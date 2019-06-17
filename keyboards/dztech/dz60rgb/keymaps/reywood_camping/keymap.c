#include QMK_KEYBOARD_H
#include "rgb_matrix.h"
#include "camping.h"

extern bool g_suspend_state;

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2

#define _______ KC_TRNS
#define KC_HGRV ALL_T(KC_GRV) // Hyper if held / Grave if tapped


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_LAYER0] = LAYOUT( /* Base */
      KC_GESC,  KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,            KC_MINS,  KC_EQL,  KC_BSPC,\
      KC_TAB,   KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,            KC_LBRC,  KC_RBRC, KC_BSLASH,\
      KC_HGRV,  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,         KC_QUOT,           KC_ENT, \
      KC_LSFT,  KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   RSFT_T(KC_SLSH), KC_UP,             LT(2, KC_DEL),\
      KC_LCTL,  KC_LALT,  KC_LGUI,                KC_SPC,                KC_RGUI,  MO(1)  , KC_LEFT,         KC_DOWN,           KC_RIGHT),

    [_LAYER1] = LAYOUT( /* FN */
      _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL ,\
      _______,  _______,  _______,  KC_UP,    _______,  _______,  KC_CALC,  _______,  KC_INS,   _______,  KC_PSCR,  KC_SLCK,  KC_PAUS,  RESET  ,\
      _______,  _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT, _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_PGUP,            _______,\
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_END,   KC_PGDOWN,KC_VOLU,            KC_MUTE,\
      _______,  _______,  _______,                      KC_MPLY,                      _______,  _______,  KC_MPRV,  KC_VOLD,            KC_MNXT),

    [_LAYER2] = LAYOUT( /* NUMPAD */
      KC_NLCK,  KC_PSLS,  KC_PAST,  KC_PMNS,  KC_PPLS,  _______,  _______,  _______,  _______,  KC_PSLS,  KC_PAST,  KC_PMNS,  KC_PPLS,  _______,\
      _______,  KC_P7,    KC_P8,    KC_P9,    _______,  _______,  _______,  _______,  KC_P7,    KC_P8,    KC_P9,    _______,  _______,  TO(0),\
      _______,  KC_P4,    KC_P5,    KC_P6,    _______,  _______,  _______,  _______,  KC_P4,    KC_P5,    KC_P6,    _______,            KC_PENT,\
      _______,  KC_P1,    KC_P2,    KC_P3,    _______,  _______,  _______,  _______,  KC_P1,    KC_P2,    KC_P3,    _______,            _______,\
      _______,  KC_P0,    KC_PDOT,                      KC_PENT,                      KC_P0,    KC_PDOT,  _______,  _______,            _______),

    };


void matrix_init_user(void) {
  camping_init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  camping_record_key_press(record);
  return true;
}

void rgb_matrix_indicators_user(void) {
  camping_scan();
}
