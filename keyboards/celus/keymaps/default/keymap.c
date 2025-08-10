// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H
#include "lib/logos.h"
#include "lib/wpm.h"

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// Use this link to search keycodes https://docs.qmk.fm/keycodes

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │   │ 6 │ 7 │ 8 │ 9 │ 0 │MUT│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │TAB│ Q │ W │ E │ R │ T │   │ Y │ U │ I │ O │ P |BSP│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SFT│ A │ S │ D │ F │  G│   │ H │ J │   │ L │ : │ENT│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │CTL│ Z │ X │ C │ V │ B │   │ N │ M │ , │ . │ / │ - │
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │L1 │   │Mac│OPT│  SPC  │ W │  `    │'  │ K │ALT│ L2│
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */
  [_QWERTY] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4, KC_5,           KC_6,   KC_7, KC_8,    KC_9,    KC_0, KC_KB_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R, KC_T,           KC_Y,   KC_U, KC_I,    KC_O,    KC_P, KC_BSPC,
        KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F, KC_G,           KC_H,   KC_J, KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V, KC_B,           KC_N,   KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
        MO(1), KC_1, KC_LGUI, KC_LOPT,KC_SPC, KC_W , KC_GRV,       KC_QUOT,  KC_K,   KC_1, MO(2)
        ),
    /*
     * LOWER
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │F1 │F2 │F3 │F4 │F5 │F6 │   │F7 │F8 │F9 │F10│F11│F12│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │ | │   │DEA│   │   │   │   │DEA│   │UP │ [ │ ] │ \ │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SFT│ ( │ ) │ { │ } │PREV│ │NEXT│LT │DEA│RT │ - │ = │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │   │ ! │ @ │ # │ $ │ % │   │ ^ │ & │ DN│ ( │ ) │   │
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │   │   │   │   │  DEL  │ Y │       │   │   │   │   │
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */
  [_LOWER] = LAYOUT(
        KC_F1, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11, KC_F12,
        KC_PIPE, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_UP,   KC_LBRC,  KC_RBRC, KC_BSLS,
        KC_NO, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_MPRV,       KC_MNXT, KC_LEFT, KC_ASTR, KC_RIGHT, KC_MINS, KC_EQL,
        KC_LSFT, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR, KC_DOWN, KC_LPRN,  KC_RPRN, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO  , KC_DEL, KC_Y,      KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO
        ),
    /*
     * _RAISE
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │   │   │   │   │   │PRV│PLY│NXT│MUT│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │   │ 7 │ 8 │ 9 │   │   │   │   │   │   │ { │ } │   │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │   │ 4 │ 5 │ 6 │   │VOL+│ │VOL-│ ( │ ) │   │   │ = │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │   │ 1 │ 2 │ 3 │   │   │   │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │   │   │ 0 │ . │  DEL  │ENT│       │   │   │   │   │
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */

  [_RAISE] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,          KC_NO,   KC_NO,   KC_MPRV,   KC_MPLY,   KC_MNXT,   KC_KB_MUTE,
        KC_NO, KC_7,  KC_8,  KC_9,   KC_NO,  KC_NO,          KC_NO,   KC_NO,   KC_NO,   KC_LCBR,   KC_RCBR,   KC_NO,
        KC_NO, KC_4,  KC_5,  KC_6,   KC_NO,  KC_VOLD,        KC_VOLU, KC_LPRN, KC_RPRN, KC_NO, KC_NO, KC_EQL,
        KC_NO, KC_1,  KC_2,  KC_3,   KC_NO,  KC_NO,          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO, KC_NO, KC_0,  KC_DOT,         KC_DEL, KC_ENT, KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO
        ),
    /*
     * This layer is not used currently
     * _ADJUST
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │   │   │   │   │       │   │       │   │   │   │   │
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */
    [_ADJUST] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_LOWER]  = { ENCODER_CCW_CW(KC_DOWN, KC_UP)  },
    [_RAISE]  = { ENCODER_CCW_CW(KC_BRIGHTNESS_UP, KC_BRIGHTNESS_DOWN)  },
    [_ADJUST] = { ENCODER_CCW_CW(KC_NO, KC_NO) },
};
#endif


bool oled_task_user(void) {
    render_lion();
    return false;
}
