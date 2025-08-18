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

// Custom keycodes for logo switching functions in logos.h file
enum custom_keycodes {
    LOGO_SWITCH = SAFE_RANGE,
    LOGO_LION,
    LOGO_FLAMENGO,
    LOGO_BAYERN,
    LOGO_RIO,
    LOGO_CELUS,
    LOGO_THEOFFICE,
    LOGO_LUNCH,
    BRAVE_OPEN,
    ZOOM_OPEN,
    NOTES_OPEN,
    WIREVPN_OPEN
};

// Variable to track current logo
static uint8_t current_logo = 0;

// Use this link to search keycodes https://docs.qmk.fm/keycodes

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     * Keyboard Image https://is.gd/MkWasy
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │   │ 6 │ 7 │ 8 │ 9 │ 0 │MUT│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │TAB│ Q │ W │ E │ R │ T │   │ Y │ U │ I │ O │ P |BSP│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │CTL│ A │ S │ D │ F │ G │   │ H │ J │ K │ L │ : │ENT│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SFT│ Z │ X │ C │ V │ B │   │ N │ M │ / │ , │ . │ - │
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │Mac│ 1 │ L1│OPT│   W   │SPC│   K   │ ' │ ` │ | │L2 │
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */
  [_QWERTY] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4, KC_5,           KC_6,   KC_7, KC_8,    KC_9,    KC_0, KC_KB_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R, KC_T,           KC_Y,   KC_U, KC_I,    KC_O,    KC_P, KC_BSPC,
        KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F, KC_G,           KC_H,   KC_J, KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V, KC_B,           KC_N,   KC_M, KC_SLSH, KC_COMM,  KC_DOT, KC_MINS,
        KC_LGUI, KC_1, MO(1), KC_LOPT, KC_W ,          KC_SPC      ,  KC_K, KC_QUOT,  KC_GRV,   KC_PIPE, MO(2)
        ),
    /*
     * LOWER
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │MCT│BDO│BUP│VPN│F5 │F6 │   │F7 │F8 │F9 │ { │ } │F12│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤        
     * │ | │ W │DEA│ W │   │   │   │DEA│ Y │ Y │ [ │ ] │DEL│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │CAP│PAD│   │ { │ } │   │   │   │LT │DEA│ K │ K │ = │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SFT│ZOO│ @ │ # │ $ │BRA│   │NOT│MCT│ \ │   │UP │ + │
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │Mac│   │   │   │ LION │LOGOS│CELUS │BAY│LEF│DOW│RIG│
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */
  [_LOWER] = LAYOUT(
    KC_MCTL, KC_BRID,   KC_BRIU,   WIREVPN_OPEN,   KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_LCBR,   KC_RCBR, KC_F12,
        KC_PIPE, KC_W,  KC_W,  KC_W,   KC_NO,   KC_NO,         KC_Y,   KC_Y,   KC_Y,   KC_LBRC,  KC_RBRC, KC_DEL,
    KC_CAPS, KC_LPAD, KC_RPRN, KC_LCBR, KC_RCBR, KC_NO,       KC_NO, KC_K, KC_K, KC_K, KC_K, KC_EQL,
    KC_LSFT, ZOOM_OPEN, KC_AT,   KC_HASH, KC_DLR,  BRAVE_OPEN,       NOTES_OPEN, KC_MCTL, KC_BSLS, KC_NO,  KC_UP, KC_PLUS,
        KC_LGUI, KC_NO, KC_NO, KC_NO  ,LOGO_LION , LOGO_SWITCH,      LOGO_CELUS,   LOGO_BAYERN,   KC_LEFT,    KC_DOWN,   KC_RIGHT
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
     * │SFT│ 1 │ 2 │ 3 │   │   │   │   │   │   │   │PGU│   │
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │Mac│   │ / │ . │FIRMWAR│ENT│       │   │   │PGD│   │
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */

  [_RAISE] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,          KC_NO,   KC_NO,   KC_MPRV,   KC_MPLY,   KC_MNXT,   KC_KB_MUTE,
        KC_NO, KC_7,  KC_8,  KC_9,   KC_NO,  KC_NO,          KC_NO,   KC_NO,   KC_NO,   KC_LCBR,   KC_RCBR,   KC_NO,
        KC_NO, KC_4,  KC_5,  KC_6,   KC_NO,  KC_VOLD,        KC_VOLU, KC_LPRN, KC_RPRN, KC_NO, KC_NO, KC_EQL,
        KC_LSFT, KC_1,  KC_2,  KC_3,   KC_NO,  KC_NO,          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PGUP,   KC_NO,
        KC_LGUI, KC_NO, KC_NO,  KC_NO,         QK_BOOT, KC_ENT, KC_NO,            KC_NO,   KC_NO,   KC_PGDN,   KC_NO
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOGO_SWITCH:
            if (record->event.pressed) {
                current_logo = (current_logo + 1) % 10; // Cycle through 0..9
            }
            break;
        case LOGO_LION:
            if (record->event.pressed) {
                current_logo = 1;
            }
            break;
        case LOGO_FLAMENGO:
            if (record->event.pressed) {
                current_logo = 0;
            }
            break;
        case LOGO_BAYERN:
            if (record->event.pressed) {
                current_logo = 2;
            }
            break;
        case LOGO_RIO:
            if (record->event.pressed) {
                current_logo = 3;
            }
            break;
        case LOGO_CELUS:
            if (record->event.pressed) {
                current_logo = 4;
            }
            break;
        case LOGO_THEOFFICE:
            if (record->event.pressed) {
                current_logo = 5;
            }
            break;
        case LOGO_LUNCH:
            if (record->event.pressed) {
                current_logo = 6;
            }
            break;
        case BRAVE_OPEN:
            if (record->event.pressed) {
                // macOS: Open Spotlight, type Brave, press Enter
                tap_code16(G(KC_SPC));
                wait_ms(200);
                SEND_STRING("Brave\n");
            }
            return false;
        case ZOOM_OPEN:
            if (record->event.pressed) {
                // macOS: Open Spotlight, type Zoom, press Enter
                tap_code16(G(KC_SPC));
                wait_ms(200);
                SEND_STRING("Zoom\n");
            }
            return false;
        case NOTES_OPEN:
            if (record->event.pressed) {
                // macOS: Open Spotlight, type Notes, press Enter
                tap_code16(G(KC_SPC));
                wait_ms(200);
                SEND_STRING("Notes\n");
            }
            return false;
        case WIREVPN_OPEN:
            if (record->event.pressed) {
                // macOS: Open Spotlight, type WireGuard, press Enter
                tap_code16(G(KC_SPC));
                wait_ms(200);
                SEND_STRING("WireGuard\n");
            }
            return false;
    }
    return true;
}

bool oled_task_user(void) {
    // Switch between logos based on current_logo variable
    switch (current_logo) {
        case 0:
            render_rio();
            break;
        case 1:
            render_lion();
            break;
        case 2:
            render_bayern();
            break;
        case 3:
            render_flamengo();
            break;
        case 4:
            render_celus();
            break;
        case 5:
            render_theoffice();
            break;
        case 6:
            render_lunch();
            break;
        default:
            render_rio();
            break;
    }
    return false;
}
