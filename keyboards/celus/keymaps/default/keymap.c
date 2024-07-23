// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lib/logos.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │   │ 6 │ 7 │ 8 │ 9 │ 0 │ ` │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │TAB│ Q │ W │ E │ R │ T │   │ Y │ U │ I │ O │ P │ - │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │L2 │ A │ S │ D │ F │ G │   │ H │ J │ K │ L │ : │ ' │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │   │ Z │ X │ C │ V │ B │   │ N │ M │ , │ . │ / │   │
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │CTR│GUI│ALT│SFT│  BSP  │L3 │  SPC  │ENT│L1 │ALT│DEL│
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_A,    KC_B,
        KC_C,    KC_D
    )

    /* [1] = LAYOUT( */
    /*     KC_X,   KC_X,   KC_X,   KC_X,   KC_X,   KC_X,       KC_X,   KC_X,   KC_X,   KC_X,   KC_X,   KC_X, */
    /*     KC_X,   KC_X,   KC_X,   KC_X,   KC_X,   KC_X,       KC_X,   KC_X,   KC_X,   KC_X,   KC_X,   KC_X, */
    /*     KC_X,   KC_X,   KC_X,   KC_X,   KC_X,   KC_X,       KC_X,   KC_X,   KC_X,   KC_X,   KC_X,   KC_X, */
    /*     KC_X,   KC_X,   KC_X,   KC_X,   KC_X,   KC_X,       KC_X,   KC_X,   KC_X,   KC_X,   KC_X,   KC_X, */
    /*     KC_X,   KC_X,   KC_X,   KC_X,       KC_X,     KC_X,     KC_X,       KC_X,   KC_X,   KC_X,   KC_X */
    /* ) */
};


bool oled_task_user(void) {
    render_charizard();
    return false;
}
