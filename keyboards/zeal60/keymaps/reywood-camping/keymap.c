// Default layout for Zeal60
#include QMK_KEYBOARD_H

enum keyboard_layers {
  _BL = 0, // Base Layer
  _FL      // Function Layer
};

#define _______ KC_TRNS
#define KC_HGRV ALL_T(KC_GRV) // Hyper if held / Grave if tapped

#define KC_RSUP RSFT_T(KC_UP)
#define KC_RADN RALT_T(KC_DOWN)
#define KC_FNLT LT(_FL, KC_LEFT)
#define KC_RCRT RCTL_T(KC_RIGHT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Default layer
[_BL] = LAYOUT_60_ansi_split_bs_rshift(
  KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, _______,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
  KC_HGRV, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSUP, KC_MPLY,
  KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                    KC_RGUI, KC_FNLT, KC_RADN, KC_RCRT),

// Fn1 Layer
[_FL] = LAYOUT_60_ansi_split_bs_rshift(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL , _______,
  _______, _______,  _______, KC_UP,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_MUTE,
  _______, _______, _______,                            KC_MPLY,                   _______, KC_MPRV, KC_VOLD, KC_MNXT),

};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}
