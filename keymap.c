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
#ifdef TRACKBALL_VERSION
#include "drivers/sensors/pimoroni_trackball.h"
#endif
enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

static uint32_t mouse_layer_timer = 0;
static bool mouse_layer_active = false;

#define MOUSE_TIMEOUT    1000   // ms
#define MOTION_THRESHOLD 5     // px
// Left-hand home row mods
#define HOME_A LCTL_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LGUI_T(KC_S)
#define HOME_T LSFT_T(KC_T)

// Right-hand home row mods
#define HOME_N RSFT_T(KC_N)
#define HOME_E RGUI_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RCTL_T(KC_O)

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L',                      'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',                      'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
                       'L', 'L', 'L', '*', '*', '*', '*', 'R', 'R', '*'
    );
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
      MS_BTN2, KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,                                          KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_PIPE,
      MS_BTN1, HOME_A,   HOME_R,   HOME_S,  HOME_T, KC_D,                    KC_H,    HOME_N,   HOME_E,  HOME_I,    HOME_O, KC_QUOT,
      QK_CAPS_WORD_TOGGLE, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,    KC_UP ,   KC_LEFT, KC_RGHT, KC_DOWN,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
      QK_CAPS_WORD_TOGGLE, KC_DEL, KC_ENT,  LT(_LOWER, KC_SPC), LT(_RAISE, KC_ESC),           LT(_RAISE, KC_ESC), LT(_LOWER, KC_SPC), KC_TAB, KC_BSPC, LGUI(LCTL(KC_Q))
    ),

    [_LOWER] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                    KC_INSERT, KC_PAUSE, KC_PSCR, _______,  _______, KC_BSLS,
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                     KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_PGUP, KC_HOME, KC_END, KC_MNXT, KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                                 _______, _______, _______, KC_SCLN, KC_EQL,  KC_EQL, KC_SCLN, _______, _______, KC_PGDN
    ),
    [_RAISE] = LAYOUT(
      _______, _______,    KC_7,    KC_8,    KC_9, KC_BSPC,                                     _______,  KC_7,    KC_8,    KC_9, _______, _______,
      _______,    KC_0,    KC_4,    KC_5,    KC_6, _______,                                  _______,  _______,    _______,    KC_6,    KC_0, _______,
      _______,    KC_0,    KC_1,    KC_2,    KC_3, KC_DOT,   _______, _______, _______, _______,_______,  KC_1,    KC_2,    KC_3,    KC_0, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_MPLY
      ),
    [_ADJUST] = LAYOUT(
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
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
                if (clockwise){
                    tap_code(KC_MNXT);
                } else{
                    tap_code(KC_MPRV);
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
                   tap_code(QK_MOUSE_WHEEL_UP);
                } else {
                   tap_code(QK_MOUSE_WHEEL_DOWN);
                }
                break;
        }
    }
    return false;
}
#endif

// Allow direction changes up to ~120° before reset
// (cos(60°) ≈ 0.5 → dot must be at least half of max possible alignment)

#define COS_HALF_DIVISOR 2   // bigger divisor = looser tolerance (e.g. 3 ≈ 70°, 4 ≈ 75°)

static inline bool should_reset(int dx, int dy, int last_dx, int last_dy) {
    long dot = (long)dx * last_dx + (long)dy * last_dy;
    if (dot <= 0) return true;  // >90° → always reset

    // Compute rough "alignment" check without sqrt
    long mag_a = (long)dx * dx + (long)dy * dy;
    long mag_b = (long)last_dx * last_dx + (long)last_dy * last_dy;

    // require dot^2 > (mag_a * mag_b) / COS_HALF_DIVISOR
    // (approx: cosθ > ~0.5 → angle < ~60° from previous direction)
    return (dot * dot) < (mag_a * mag_b) / COS_HALF_DIVISOR;
}

static uint16_t last_move_time = 0;
static int16_t momentum = 100; // percent (100 = 1.0x)

#define MOMENTUM_STEP 15       // how quickly it grows per tick
#define MOMENTUM_DECAY 4       // how quickly it shrinks when idle
#define MOMENTUM_MIN   80      // 0.8x scaling for precision
#define MOMENTUM_MAX  1500      // 15.0x max speed


// --- Mouse motion handling ---
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    uint16_t motion = abs(mouse_report.x) + abs(mouse_report.y);
    int16_t dx = mouse_report.x;
    int16_t dy = mouse_report.y;

    if (motion > MOTION_THRESHOLD) {
        if (!mouse_layer_active) {
            layer_on(_RAISE);
            mouse_layer_active = true;
        }
        // keep extending the timer
        mouse_layer_timer = timer_read32();
    }

    if (mouse_layer_active && timer_elapsed32(mouse_layer_timer) > MOUSE_TIMEOUT) {
        layer_off(_RAISE);
        mouse_layer_active = false;
    }


    if (dx || dy) {
        uint16_t now = timer_read();
        uint16_t dt = now - last_move_time;
        last_move_time = now;

        if (dt < 50) {
            momentum += MOMENTUM_STEP;
            if (momentum > MOMENTUM_MAX) momentum = MOMENTUM_MAX;
        } else {
            momentum -= MOMENTUM_DECAY;
            if (momentum < MOMENTUM_MIN) momentum = MOMENTUM_MIN;
        }

        mouse_report.x = (dx * momentum) / 100;
        mouse_report.y = (dy * momentum) / 100;

        uprintf("dx=%d dy=%d dt=%u momentum=%d scaled=(%d,%d)\n",
                dx, dy, dt, momentum,
                mouse_report.x, mouse_report.y);
    } else {
        if (momentum > MOMENTUM_MIN) {
            momentum -= MOMENTUM_DECAY;
            if (momentum < MOMENTUM_MIN) momentum = MOMENTUM_MIN;
        }
    }

    return mouse_report;
}
