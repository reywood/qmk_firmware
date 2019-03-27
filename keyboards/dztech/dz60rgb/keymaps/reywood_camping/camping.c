#include "quantum.h"
// #include "rgb_backlight.h"

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define MIN_HUE 0
#define MAX_HUE 20
#define MIN_BRIGHTNESS 20
#define MAX_BRIGHTNESS 200
#define SATURATION 250
#define HUE_FLICKER_STEP 5
#define BRIGHTNESS_FLICKER_STEP 5
#define INVALID_LED 255

static uint8_t current_led_brightness[DRIVER_LED_TOTAL];
static uint8_t current_led_hue[DRIVER_LED_TOTAL];

static void map_row_column_to_key_led(uint8_t row, uint8_t column, uint8_t *led) {
    rgb_led current_led;

    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        current_led = g_rgb_leds[i];
        if (row == current_led.matrix_co.row && column == current_led.matrix_co.col) {
            *led = i;
            return;
        }
    }

    *led = INVALID_LED;
}

static uint8_t random_flicker(uint8_t value, uint8_t step, uint8_t min, uint8_t max) {
    uint8_t step_up = MIN(step, max - value);
    uint8_t step_down = -MIN(step, value);
    uint8_t new_value = value + ((rand() % 2 == 0) ? step_down : step_up);
    return MAX(MIN(new_value, max), min);
}

static bool has_enough_time_passed(uint8_t *tick) {
  if (*tick < 8) {
    (*tick)++;
    return FALSE;
  }
  *tick = 0;
  return TRUE;
}

static void update_esc_hue_and_brightness(uint8_t *hue, uint8_t *brightness) {
  static uint8_t update_tick = 0;
  if (!has_enough_time_passed(&update_tick)) { return; }

  *hue = random_flicker(*hue, HUE_FLICKER_STEP, MIN_HUE, MAX_HUE);
  *brightness = random_flicker(*brightness, BRIGHTNESS_FLICKER_STEP, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
}

static void update_esc_flicker(void) {
  static uint8_t esc_current_hue = 0;
  static uint8_t esc_current_brightness = 30;

  update_esc_hue_and_brightness(&esc_current_hue, &esc_current_brightness);
  HSV esc_hsv = { .h = esc_current_hue, .s = SATURATION, .v = esc_current_brightness };
  RGB esc_rgb = hsv_to_rgb(esc_hsv);

  uint8_t esc_led;
  map_row_column_to_key_led(0, 0, &esc_led);
  if (esc_led != INVALID_LED) {
    rgb_matrix_set_color(esc_led, esc_rgb.r, esc_rgb.g, esc_rgb.b);
  }
}

static void update_key_flicker(uint8_t led) {
  if (current_led_brightness[led] > 0) {
    HSV hsv = { .h = current_led_hue[led], .s = SATURATION, .v = current_led_brightness[led] };
    RGB rgb = hsv_to_rgb(hsv);

    rgb_matrix_set_color(led, rgb.r, rgb.g, rgb.b);
  } else {
    rgb_matrix_set_color(led, 0, 0, 0);
  }
}

static void update_all_key_brightnesses_and_hues(void) {
  static uint8_t update_tick = 0;
  if (!has_enough_time_passed(&update_tick)) { return; }

  for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
    if (current_led_brightness[i] > 0) {
      current_led_brightness[i]--;
      current_led_brightness[i] = random_flicker(current_led_brightness[i], BRIGHTNESS_FLICKER_STEP, 0, MAX_BRIGHTNESS);
      current_led_hue[i] = random_flicker(current_led_hue[i], HUE_FLICKER_STEP, MIN_HUE, MAX_HUE);
    }
  }
}

void camping_init(void) {
  for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
    current_led_brightness[i] = 0;
  }
}

void camping_scan(void) {
  update_all_key_brightnesses_and_hues();

  uint8_t esc_led;
  map_row_column_to_key_led(0, 0, &esc_led);

  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    if (i == esc_led) {
      update_esc_flicker();
    } else {
      update_key_flicker(i);
    }
  }
}

void camping_record_key_press(keyrecord_t *record) {
  uint8_t led;
  map_row_column_to_key_led(record->event.key.row, record->event.key.col, &led);
  if (led >= 0 && led < DRIVER_LED_TOTAL) {
    current_led_brightness[led] = MAX_BRIGHTNESS;
  }
}
