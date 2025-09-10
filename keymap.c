/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
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
#include "sm_td.h"

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

// enum custom_keycodes {
    // DND15 = SAFE_RANGE,, /* Slack "Do not disturb 25 mins" */
    // DND30,
    // DND60,
// };
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
      MS_BTN2, KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,                                         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_PIPE,
      MS_BTN1, KC_A,   KC_R,   KC_S,   KC_T,   KC_D,                                         KC_H,    KC_N,   KC_E,  KC_I,    KC_O, KC_QUOT,
      MS_BTN1, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,    KC_UP,   KC_LEFT, KC_RGHT, LGUI(LCTL(KC_Q)), KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
      QK_CAPS_WORD_TOGGLE, KC_DEL, KC_ENT, LT(_LOWER, KC_SPC), LT(_RAISE, KC_ESC),                       MO(_RAISE), LT(_LOWER, KC_SPC), KC_TAB,  KC_BSPC, KC_DOWN
    ),

    [_LOWER] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                    KC_INSERT, KC_PAUSE, KC_PSCR, _______,  _______, KC_BSLS,
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                     KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_PGUP, KC_HOME, KC_END, KC_MNXT, KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                                 _______, _______, _______, KC_SCLN, KC_EQL,  KC_EQL, KC_SCLN, _______, _______, KC_PGDN
    ),
    [_RAISE] = LAYOUT(
      _______, _______,    KC_7,    KC_8,    KC_9, KC_DEL,                                      RM_TOGG, RM_SPDU, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT,
      _______,    KC_0,    KC_4,    KC_5,    KC_6, KC_BSPC,                                     _______, RM_SPDD, RM_SATD, RM_HUED, RM_VALD, RM_PREV,
      _______,    KC_0,    KC_1,    KC_2,    KC_3, KC_DOT,   _______, _______, _______, _______,_______,  KC_1,    KC_2,    KC_3,    KC_0, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_MPLY
      ),
    [_ADJUST] = LAYOUT(
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      RM_TOGG, RM_SPDU, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, RM_SPDD, RM_SATD, RM_HUED, RM_VALD, RM_PREV,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // uprintf("index %d, clockwise %d\n", index, clockwise);

    if (index == 1) {
        switch(biton32(layer_state)){
            case _ADJUST:
                // uprintf("ADJUST\n");
                if (clockwise){
                    tap_code16(C(KC_A));
                    // was slow
                    //send_string(":resize-p -D 5");
                    //tap_code(KC_ENTER);
                    tap_code16(S(KC_J));
                } else{
                    tap_code16(C(KC_A));
                    /* was slow */
                    /* send_string(":resize-p -U 5"); */
                    /* tap_code(KC_ENTER); */
                    tap_code16(S(KC_K));
                }
                break;

            case _RAISE:
                // uprintf("RAISE\n");
                if (clockwise){
                    tap_code(KC_VOLU);
                } else{
                    tap_code(KC_VOLD);
                }
                break;

            case _LOWER:
                // uprintf("LOWER\n");
                if (clockwise){
                    tap_code16(S(KC_SCLN));
                    tap_code(KC_C);
                    tap_code(KC_N);
                    tap_code(KC_ENTER);
                } else{
                    tap_code16(S(KC_SCLN));
                    tap_code(KC_C);
                    tap_code(KC_P);
                    tap_code(KC_ENTER);
                }
                break;

              default:
                // uprintf("QWERTY\n");
                // Page up/Page down
                if (clockwise) {
                   tap_code(KC_PGDN);
                } else {
                   tap_code(KC_PGUP);
                }
                break;
        }
    }
    return false;
}
#endif


smtd_resolution on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(KC_A, KC_LEFT_CTRL)
        SMTD_MT(KC_R, KC_LEFT_ALT)
        SMTD_MT(KC_S, KC_LEFT_GUI)
        SMTD_MT(KC_T, KC_LSFT)
        SMTD_MT(KC_O, KC_RIGHT_CTRL)
        SMTD_MT(KC_I, KC_LEFT_ALT)
        SMTD_MT(KC_E, KC_LEFT_GUI)
        SMTD_MT(KC_N, KC_LSFT)
        SMTD_MT(KC_ENT, KC_LEFT_ALT)
    }

    return SMTD_RESOLUTION_UNHANDLED;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
         return false;
    }
    return true;
}
