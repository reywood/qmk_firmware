/* Copyright 2017 Zach White <skullydazed@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define ______ KC_TRNS

#define LU 1  // layer up
#define LD 2  // layer down

enum my_keycodes {
    DEFCON1 = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_2u_ansi( \
                                    KC_BTN1, KC_BTN2,                                                                                                                 KC_BTN3, KC_BTN4,                                   \
        KC_HOME, KC_END,  KC_PGUP, KC_PGDN,        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,   KC_F11,  KC_F12,         KC_PSCR, KC_SLCK, KC_PAUS, KC_INS,  \
                                                                                                                                                                                                                          \
        KC_PMNS, KC_NLCK, KC_PSLS, KC_PAST,        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_BSPC,       KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
        KC_PPLS, KC_P7,   KC_P8,   KC_P9,          KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSLS,       KC_P7,   KC_P8,   KC_P9,   KC_PSLS, \
                 KC_P4,   KC_P5,   KC_P6,          KC_CAPS,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,      KC_ENT,       KC_P4,   KC_P5,   KC_P6,            \
        KC_PENT, KC_P1,   KC_P2,   KC_P3,      KC_UP,   KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM, KC_DOT, KC_SLSH,   KC_RSFT,        KC_UP,      KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
                 KC_P0,   KC_PDOT,   KC_LEFT, KC_DOWN, KC_RGHT,   KC_LCTL, KC_LALT, KC_LGUI, MO(LD),   KC_SPC,  MO(LU), KC_RGUI, KC_RALT, MO(LU), KC_RCTL,      KC_LEFT, KC_DOWN, KC_RGHT,     KC_P0,   KC_PDOT           \
    ),
    [LU] = LAYOUT_2u_ansi( \
                                    ______, ______,                                                                                                                 ______, ______,                                      \
        ______,  ______,  ______,  ______,         ______,    ______,  ______,  ______,  ______,    ______,  ______,  ______,  ______,    ______,  ______,   ______,  ______,         ______,  ______,  ______,  ______, \
                                                                                                                                                                                                                         \
        KC_WH_L, KC_WH_R, KC_BTN3, ______,         ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______, ______,        ______,  ______,  ______,  ______, \
        KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2,        ______,    ______,  ______,  KC_UP,   ______,  ______,  ______,  ______,  ______,  ______,  ______, ______, ______, ______,        ______,  ______,  ______,  ______, \
                 KC_MS_L, KC_MS_D, KC_MS_R,        ______,      ______,  KC_LEFT, KC_DOWN, KC_RGHT, ______,  ______,  ______,  ______,  ______,  ______, ______,       ______,        ______,  ______,  ______,          \
        KC_WH_D, KC_ACL0, KC_ACL1, KC_ACL2,  ______,     ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______, ______, ______, ______,   ______,       KC_VOLU,      ______,  ______,  ______,  ______, \
                 ______,  ______,    ______, ______, ______,      ______,  ______,  ______,  ______,   KC_MPLY, ______, ______,  ______,  ______, ______,      KC_MRWD, KC_VOLD, KC_MFFD,      ______,  ______           \
    ),
    [LD] = LAYOUT_2u_ansi( \
                                    ______, ______,                                                                                                                 ______, ______,                                      \
        ______,  ______,  ______,  ______,         ______,    ______,  ______,  ______,  ______,    ______,  ______,  ______,  ______,    ______,  ______,   ______,  ______,         ______,  ______,  ______,  ______, \
                                                                                                                                                                                                                         \
        ______,  ______,  ______,  ______,         ______,  DEFCON1, ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______, ______,        ______,  ______,  ______,  ______, \
        RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,        ______,    ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______, ______, ______, ______,        ______,  ______,  ______,  ______, \
                 RGB_HUD, RGB_SAD, RGB_VAD,        ______,      ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______, ______,       ______,        ______,  ______,  ______,          \
        RGB_RMOD,______,  ______,  ______,    RGB_MOD,   ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______, ______, ______, ______,   ______,       CK_UP,        ______,  ______,  ______,  ______, \
                 ______,  ______,    RGB_VAD, RGB_RMOD, RGB_VAI,  ______,  ______,  ______,  ______,   MU_TOG,  MU_MOD, ______,  ______,  ______, ______,      CK_TOGG, CK_DOWN,  CK_RST,      ______,  ______           \
    ),
};


// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    // #ifdef AUDIO_ENABLE
    //     PLAY_SONG(SONG(WORKMAN_SOUND));
    // #endif
};

// void cycle_through_leds() {
//     static uint8_t current_led = 0;
//     for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
//         if (i == current_led) {
//             rgb_matrix_set_color(i, 0xff, 0x00, 0xff);
//         } else {
//             rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
//         }
//     }
//     current_led++;
//     if (current_led >= DRIVER_LED_TOTAL) {
//         current_led = 0;
//     }
// }


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // cycle_through_leds();
        if (keycode == ENC_BTN1) {

        }

        if (keycode == DEFCON1) {
            uint16_t red = 0;
            rgb_matrix_sethsv(red, 255, 255);
            rgb_matrix_mode(RGB_MATRIX_BAND_PINWHEEL_VAL);
        }
    }

    return true;
}


// #ifdef AUDIO_ENABLE
// float song_caps_on  [][2] = SONG(CAPS_LOCK_ON_SOUND);
// float song_caps_off [][2] = SONG(CAPS_LOCK_OFF_SOUND);

// static bool is_caps_lock_turning_on(uint8_t usb_led, uint8_t old_usb_led) {
//     return (usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK));
// }

// static bool is_caps_lock_turning_off(uint8_t usb_led, uint8_t old_usb_led) {
//     return !(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK));
// }

// void led_set_user(uint8_t usb_led) {
//     static uint8_t old_usb_led = 0;
//     // _delay_ms(10);                            // gets rid of tick
//     if (!is_playing_notes()) {
//         if (is_caps_lock_turning_on(usb_led, old_usb_led)) {
//             PLAY_SONG(song_caps_on);
//         }
//         else if (is_caps_lock_turning_off(usb_led, old_usb_led)) {
//             PLAY_SONG(song_caps_off);
//         }
//     }
//     old_usb_led = usb_led;
// }
// #endif


