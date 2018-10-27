#include "quantum.h"
#include "rgblight.h"
#include "rgb_ripple.h"

#define RGB_SUSTAIN 0.7
#define RGB_PROPAGATE 0.1
#define RGB_HIT 0xff
#define RGB_REFRESH_INTERVAL_IN_MS 20

#define TOTAL_ROWS 6
#define TOTAL_COLUMNS 16
#define TOTAL_RGBLEDS_ACROSS (RGBLED_NUM / 2)

static uint16_t last_rgb_update;
static uint8_t rgb_state[RGBLED_NUM];

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

int get_current_value_at_rgb_position(int rgb_led_position) {
  if (rgb_led_position >= 0 && rgb_led_position < RGBLED_NUM) {
    return rgb_state[rgb_led_position];
  }
  return 0;
}

int get_propagated_value_from_left_neighbor(int rgb_led_position) {
  bool is_top_row = rgb_led_position < (RGBLED_NUM / 2);
  int left_neighbor = is_top_row ? rgb_led_position - 1 : rgb_led_position + 1;
  return get_current_value_at_rgb_position(left_neighbor) * RGB_PROPAGATE;
}

int get_propagated_value_from_right_neighbor(int rgb_led_position) {
  bool is_top_row = rgb_led_position < (RGBLED_NUM / 2);
  int right_neighbor = is_top_row ? rgb_led_position + 1 : rgb_led_position - 1;
  return get_current_value_at_rgb_position(right_neighbor) * RGB_PROPAGATE;
}

int get_propagated_value_from_neighbors(int rgb_led_position) {
  return get_propagated_value_from_left_neighbor(rgb_led_position) +
         get_propagated_value_from_right_neighbor(rgb_led_position);
}

void calculate_new_rgb_states(uint8_t* new_rgb_states) {
  for (int i = 0; i < RGBLED_NUM; i++) {
    // Diminish current value
    new_rgb_states[i] = rgb_state[i] * RGB_SUSTAIN;

    new_rgb_states[i] += get_propagated_value_from_neighbors(i);
  }
}

void set_new_rgb_states(uint8_t* new_rgb_states) {
  for (int i = 0; i < RGBLED_NUM; i++) {
    rgb_state[i] = new_rgb_states[i];
    led[i].r = rgb_state[i];
    led[i].g = rgb_state[i] * 0.2;
    led[i].b = 0;
  }
  rgblight_set();
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

int map_key_to_rgb_position(keypos_t key) {
  int base_position = ((float)key.col / TOTAL_COLUMNS) * TOTAL_RGBLEDS_ACROSS;

  if (key.row <= (TOTAL_ROWS / 2) - 1) {
    return base_position;
  } else if (key.row < TOTAL_ROWS) {
    return RGBLED_NUM - base_position - 1;
  }

  return -1;
}

void set_nearest_rgb_to_max(keypos_t key) {
    int rgb_position = map_key_to_rgb_position(key);
    if (rgb_position >= 0 && rgb_position < RGBLED_NUM) {
      rgb_state[rgb_position] = RGB_HIT;
    }
}

void rgb_ripple_record_key_press(keyrecord_t *record) {
  #ifdef RGBLIGHT_ENABLE
  if (record->event.pressed) {
    set_nearest_rgb_to_max(record->event.key);
  }
  #endif
}
