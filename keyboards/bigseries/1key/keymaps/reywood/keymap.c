/*
Copyright 2018 Cole Markham

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H


enum custom_keycodes {
  HYPER_A = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT(HYPER_A),
};


bool initialized = 0;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  return MACRO_NONE ;
}

void matrix_init_user(void) {
  if (!initialized) {
    dprintf("Initializing in matrix_scan_user");
    rgblight_enable();
    rgblight_sethsv(0, 255, 255);
    rgblight_setrgb(0x00, 0x00, 0xFF);
    rgblight_mode(7);
    initialized = 1;
  }
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case HYPER_A:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LALT) SS_DOWN(X_LGUI) SS_DOWN(X_LSHIFT)
                    SS_TAP(X_A)
                    SS_UP(X_LCTRL) SS_UP(X_LALT) SS_UP(X_LGUI) SS_UP(X_LSHIFT));
        return false;
      }
      break;

    case KC_A:
      if (record->event.pressed) {
        SEND_STRING("Howdy!!\n");
        rgblight_step();
        return false;
      }
      break;
  }
  return true;
}
