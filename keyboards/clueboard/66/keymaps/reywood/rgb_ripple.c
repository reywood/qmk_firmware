#include "quantum.h"
#include "rgblight.h"
#include "rgb_ripple.h"

/*
LED layout as seen from above:
/---------------------------\
|  10 11 12 13 14 15 16 17  |
| 9                       0 |
|   8  7  6  5  4  3  2  1  |
\---------------------------/

rows and columns:
 --------------------------------------------
|   | 0 1 2 3 4 5 6 7    |   | 0 1 2 3 4 5 6 |
 ---------------------------------------------
| 0 | E 1 2 3 4 5 6 7    | 5 | 8 9 0 - = B P |
| 1 | T q w e r t y u    | 6 | i o p [ ] \ P |
| 2 | C a s d f g h j    | 7 | k l ; ' E     |
| 3 | S z x c v b n      | 8 | m , . / D S U |
| 4 | C A W Space        | 9 | W F A L D R   |
 --------------------------------------------
*/

#define RGB_SUSTAIN 0.7
#define RGB_PROPAGATE 0.1
#define RGB_HIT 0xff
#define RGB_REFRESH_INTERVAL_IN_MS 20

#define TOTAL_ROWS 5
#define TOTAL_COLUMNS 16
#define TOTAL_RGBLEDS_ACROSS 8
#define VIRTUAL_COLUMN_SPLIT_BOUNDARY 8

#define TOP_LEFT_RGB_POSITION 10
#define TOP_RIGHT_RGB_POSITION 17
#define BOTTOM_LEFT_RGB_POSITION 8
#define BOTTOM_RIGHT_RGB_POSITION 1

#define MIN_R 0x45
#define MIN_G 0x00
#define MIN_B 0x0e
#define MAX_R 0xff
#define MAX_G 0x00
#define MAX_B 0x34

static uint16_t last_rgb_update;
static uint8_t rgb_state[RGBLED_NUM];

static uint8_t calculate_physical_row(uint8_t virtual_row) {
  if (virtual_row >= TOTAL_ROWS) {
    return virtual_row - TOTAL_ROWS;
  }
  return virtual_row;
}

static uint8_t calculate_physical_col(uint8_t virtual_row, uint8_t virtual_col) {
  if (virtual_row >= TOTAL_ROWS) {
    return virtual_col + VIRTUAL_COLUMN_SPLIT_BOUNDARY;
  }
  return virtual_col;
}

static int get_current_value_at_rgb_position(int rgb_led_position) {
  if (rgb_led_position >= 0 && rgb_led_position < RGBLED_NUM) {
    return rgb_state[rgb_led_position];
  }
  return 0;
}

// int get_propagated_value_from_left_neighbor(int rgb_led_position) {
//   bool is_top_row = rgb_led_position < (RGBLED_NUM / 2);
//   int left_neighbor = is_top_row ? rgb_led_position - 1 : rgb_led_position + 1;
//   return get_current_value_at_rgb_position(left_neighbor) * RGB_PROPAGATE;
// }

// int get_propagated_value_from_right_neighbor(int rgb_led_position) {
//   bool is_top_row = rgb_led_position < (RGBLED_NUM / 2);
//   int right_neighbor = is_top_row ? rgb_led_position + 1 : rgb_led_position - 1;
//   return get_current_value_at_rgb_position(right_neighbor) * RGB_PROPAGATE;
// }

static int get_propagated_value_from_neighbors(int rgb_led_position) {
  if (rgb_led_position == 0) {
    return get_current_value_at_rgb_position(1) * RGB_PROPAGATE +
           get_current_value_at_rgb_position(RGBLED_NUM - 1) * RGB_PROPAGATE;
  }
  if (rgb_led_position == RGBLED_NUM - 1) {
    return get_current_value_at_rgb_position(0) * RGB_PROPAGATE +
           get_current_value_at_rgb_position(RGBLED_NUM - 2) * RGB_PROPAGATE;
  }
  return get_current_value_at_rgb_position(rgb_led_position - 1) * RGB_PROPAGATE +
         get_current_value_at_rgb_position(rgb_led_position + 1) * RGB_PROPAGATE;

  // return get_propagated_value_from_left_neighbor(rgb_led_position) +
  //        get_propagated_value_from_right_neighbor(rgb_led_position);
}

static void calculate_new_rgb_states(uint8_t* new_rgb_states) {
  for (int i = 0; i < RGBLED_NUM; i++) {
    // Diminish current value
    new_rgb_states[i] = rgb_state[i] * RGB_SUSTAIN;

    new_rgb_states[i] += get_propagated_value_from_neighbors(i);
  }
}

static uint8_t calculate_new_color_component_value(uint8_t max, uint8_t min, uint8_t current_boost) {
  return (float)(max - min) * current_boost / 100 + min;
}

static void set_new_rgb_states(uint8_t* new_rgb_states) {
  for (int i = 0; i < RGBLED_NUM; i++) {
    rgb_state[i] = new_rgb_states[i];
    led[i].r = calculate_new_color_component_value(MAX_R, MIN_R, rgb_state[i]);
    led[i].g = calculate_new_color_component_value(MAX_G, MIN_G, rgb_state[i]);
    led[i].b = calculate_new_color_component_value(MAX_B, MIN_B, rgb_state[i]);
  }
  rgblight_set();
}

static int map_key_to_rgb_position(keypos_t key) {
  uint8_t row = calculate_physical_row(key.row);
  uint8_t col = calculate_physical_col(key.row, key.col);
  int base_position = ((float)col / TOTAL_COLUMNS) * TOTAL_RGBLEDS_ACROSS;

  if (row <= (TOTAL_ROWS / 2) - 1) {
    return TOP_LEFT_RGB_POSITION + base_position;
  } else if (row < TOTAL_ROWS) {
    return BOTTOM_LEFT_RGB_POSITION - base_position;
  }

  return -1;
}

static void set_nearest_rgb_to_max(keypos_t key) {
    int rgb_position = map_key_to_rgb_position(key);
    if (rgb_position >= 0 && rgb_position < RGBLED_NUM) {
      rgb_state[rgb_position] = 100;
    }
}

void rgb_ripple_init(void) {
  #ifdef RGBLIGHT_ENABLE
  last_rgb_update = timer_read();
  rgblight_enable();
  rgblight_setrgb(0, 0, 0);

  for (int i = 0; i < RGBLED_NUM; i++) {
    rgb_state[i] = 0;
  }
  #endif
}

void rgb_ripple_update_display(void) {
  #ifdef RGBLIGHT_ENABLE

  if (timer_elapsed(last_rgb_update) > RGB_REFRESH_INTERVAL_IN_MS) {
    last_rgb_update = timer_read();

    uint8_t new_rgb_states[RGBLED_NUM];
    calculate_new_rgb_states(new_rgb_states);
    set_new_rgb_states(new_rgb_states);
  }

  #endif
}

void rgb_ripple_record_key_press(keyrecord_t *record) {
  #ifdef RGBLIGHT_ENABLE
  if (record->event.pressed) {
    set_nearest_rgb_to_max(record->event.key);
  }
  #endif
}
