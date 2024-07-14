// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

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



#define OLED_PIXELS_HEIGHT 128
#define OLED_PIXELS_WIDTH 64
#define OLED_PIXELS_PIXELS (OLED_PIXELS_HEIGHT * OLED_PIXELS_WIDTH)
#define OLED_PIXELS_BYTES (OLED_PIXELS_PIXELS / 8)
#define BLACK 0
#define WHITE 1

//bool oled_task_user(void) {
//    // Init
//    char *pixels = malloc(OLED_PIXELS_BYTES);
//    memset(pixels, BLACK, OLED_PIXELS_BYTES);
//
//    // Write to OLED
//    oled_write_raw(pixels, OLED_PIXELS_BYTES);
//
//    return false;
//}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("Test\n"), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
#endif
