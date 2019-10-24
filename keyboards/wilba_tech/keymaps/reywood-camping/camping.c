#include "quantum.h"
#include "rgb_backlight.h"

#define MIN_HUE 0
#define MAX_HUE 20
#define MIN_BRIGHTNESS 20
#define MAX_BRIGHTNESS 200
#define SATURATION 250
#define HUE_FLICKER_STEP 5
#define BRIGHTNESS_FLICKER_STEP 5

extern uint8_t g_key_hit[BACKLIGHT_LED_COUNT];
extern void map_row_column_to_led( uint8_t row, uint8_t column, uint8_t *led );


static uint8_t g_key_hue[BACKLIGHT_LED_COUNT];

static uint8_t random_flicker(uint8_t value, uint8_t step, uint8_t min, uint8_t max) {
    uint8_t step_up = MIN(step, max - value);
    uint8_t step_down = -MIN(step, value);
    uint8_t new_value = value + ((rand() % 2 == 0) ? step_down : step_up);
    return MAX(MIN(new_value, max), min);
}

static void camping_update_esc_flicker(void) {
    static uint8_t esc_current_hue = 0;
    static uint8_t esc_current_brightness = 30;

    uint8_t esc_led;
    map_row_column_to_led(0, 0, &esc_led);

    esc_current_hue = random_flicker(esc_current_hue, HUE_FLICKER_STEP, MIN_HUE, MAX_HUE);
    esc_current_brightness = random_flicker(esc_current_brightness, BRIGHTNESS_FLICKER_STEP, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
    HSV esc_hsv = { .h = esc_current_hue, .s = SATURATION, .v = esc_current_brightness };
    RGB esc_rgb = hsv_to_rgb(esc_hsv);
    backlight_set_color(esc_led, esc_rgb.r, esc_rgb.g, esc_rgb.b);
}

static void camping_update_key_flicker(uint8_t led) {
    uint8_t brightness = MAX(MAX_BRIGHTNESS - g_key_hit[led], 0);
    if (brightness > 0) {
        g_key_hue[led] = random_flicker(g_key_hue[led], HUE_FLICKER_STEP, MIN_HUE, MAX_HUE);
        brightness = random_flicker(brightness, BRIGHTNESS_FLICKER_STEP, 0, MAX_BRIGHTNESS);

        HSV hsv = { .h = g_key_hue[led], .s = SATURATION, .v = brightness };
        RGB rgb = hsv_to_rgb(hsv);

        backlight_set_color(led, rgb.r, rgb.g, rgb.b);
    } else {
        backlight_set_color(led, 0, 0, 0);
    }
}

void backlight_effect_camping(void) {
    uint8_t esc_led;
    map_row_column_to_led(0, 0, &esc_led);

    for (int i = 0; i < BACKLIGHT_LED_COUNT; i++) {
        if (i == esc_led) {
            camping_update_esc_flicker();
        } else {
            camping_update_key_flicker(i);
        }
    }
}
