/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
/*
 * Base Layer:
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |   Q  |   W  |   F  |   P  |   G  |                              |   J  |   L  |   U  |   Y  |   ;  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   A  |   R  |   S  |  T   |   D  |                              |   H  |   N  |   E  |   I  |   O  |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |LwrUpt|RseLft|  |Right |Down  |K/ALT |M/GUI | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | Del  | Enter| Space| Enter|  | Enter| Space| Tab  | Bksp | Lock |
 *                        |      |      |Lower | Ctrl | Shift|  | Raise| Lower|Lower |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */

    [_QWERTY] = LAYOUT(
      KC_MS_BTN2,              KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,                                         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_PIPE,
      KC_LCTL,                 KC_A,   KC_R,   KC_S,   KC_T,   KC_D,                                         KC_H,    KC_N,   KC_E,  KC_I,    KC_O, KC_QUOT,
      KC_LSFT,                 KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,    KC_UP,   KC_LEFT, KC_RGHT, KC_DOWN,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
      KC_LGUI, KC_DEL, KC_ENT, KC_SPC, KC_ESC, MO(_LOWER),                       KC_SPC, KC_TAB,  KC_BSPC, LGUI(LCTL(KC_Q))
    ),
/*
 * Lower Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |      |      |      |      |  £   |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                              |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |  ;   |  =   |  |  =   |  ;   |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                    KC_INSERT, KC_PAUSE, KC_PSCR, _______,  _______, KC_BSLS,
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                     KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_PGUP, KC_HOME, KC_END, KC_PGDN, KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                                 _______, _______, _______, KC_SCLN, KC_EQL,  KC_EQL, KC_SCLN, _______, _______, KC_MNXT
    ),
/*
 * Raise Layer: Number keys, media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | Next | VolUp|                              | Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      | Mute | VolDn|      |      |  |      |      | MLeft| Mdown| MUp  |MRight|      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
      _______, _______,    KC_7,    KC_8,    KC_9, KC_DEL,                                     _______,  KC_7,    KC_8,    KC_9, _______, _______,
      _______,    KC_0,    KC_4,    KC_5,    KC_6, KC_BSPC,                                     _______,  KC_4,    KC_5,    KC_6,    KC_0, _______,
      _______,    KC_0,    KC_1,    KC_2,    KC_3, KC_DOT,   KC_MS_U, KC_MS_L, KC_MS_R, KC_MS_D,_______,  KC_1,    KC_2,    KC_3,    KC_0, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_MPLY
      ),
    /*
     * Adjust Layer: Function keys, RGB
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      | F11  | F12  |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_ADJUST] = LAYOUT(
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_status(void) {
    oled_write_P(PSTR("Cparsons rev1.19\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    }
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 1) {
        switch(biton32(layer_state)){
            case _ADJUST:
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
                if (clockwise){
                    tap_code(KC_VOLD);
                } else{
                    tap_code(KC_VOLU);
                }
                break;

            case _LOWER:
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
                // Page up/Page down
                if (clockwise) {
                   tap_code(KC_PGUP);
                } else {
                   tap_code(KC_PGDN);
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
        SMTD_LT(KC_SPC, _LOWER)
        SMTD_LT(KC_ESC, _RAISE)
        SMTD_LT(KC_TAB, _RAISE)
    }

    return SMTD_RESOLUTION_UNHANDLED;
}

static uint16_t f13_timer = 0;
static bool waiting_to_release = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case KC_F13:
            if (record->event.pressed) {
                // Motion started
                layer_on(_RAISE);
                waiting_to_release = false;
            } else {
                // Motion stopped -> start decay timer
                f13_timer = timer_read();
                waiting_to_release = true;
            }
            return false; // suppress actual F13 keystroke
    }
    return true;
}

void matrix_scan_user(void) {
    if (waiting_to_release && timer_elapsed(f13_timer) > 500) {
        layer_off(_RAISE);
        waiting_to_release = false;
    }
}
