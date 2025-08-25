// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H
#include "lib/logos.h"
#include "lib/wpm.h"
// Standard headers for types used in some IDE linters
#include <stdint.h>
#include <stdbool.h>

// Helper to open apps via macOS Spotlight (Cmd+Space -> type -> Enter)
static void open_using_spotlight(const char *name);

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
    LOGO_TOMORROWLAND,
    BRAVE_OPEN,
    ZOOM_OPEN,
    NOTES_OPEN,
    WIREVPN_OPEN,
    SAFARI_OPEN,
    FIREFOX_OPEN,
    MATTERMOST_OPEN,
    CALCULATOR_OPEN,
    MONITOR_OPEN,
    AWS_SSO,
    TERMINAL_OPEN
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
     * │CTL│ A │ S │ D │ G │ F │   │ H │ J │ K │ L │ ` │ENT│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SFT│ Z │ X │ C │ V │ B │   │ N │ M │ / │ ' │ ; │SFT│
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │Mac│ L1│ = │OPT│  MCL  │SPC│   |   │ , │ . │ L2│ - │
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */
  [_QWERTY] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4, KC_5,           KC_6,   KC_7, KC_8,    KC_9,    KC_0, KC_KB_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R, KC_T,           KC_Y,   KC_U, KC_I,    KC_O,    KC_P, KC_BSPC,
        KC_LCTL,   KC_A,    KC_S,    KC_D,   KC_G, KC_F,           KC_H,   KC_J, KC_K,    KC_L,    KC_GRV, KC_ENT,
        KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V, KC_B,           KC_N,   KC_M, KC_SLSH, KC_QUOT,  KC_SCLN, KC_RSFT,
        KC_LGUI, MO(1), KC_EQL, KC_LOPT, KC_MCTL ,          KC_SPC      ,  KC_PIPE, KC_COMM,  KC_DOT,   MO(2), KC_MINS
        ),
    /*
     * LOWER
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │PAD│BDO│BUP│VPN│CAL│CPU│   │ZOO│F8 │F9 │ { │ } │F12│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SAF│   │   │   │RIO│TER│   │   │   │   │ [ │ ] │DEL│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │CAP│AWS│   │   │   │FRX│   │   │   │   │   │   │ = │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SFT│   │   │   │   │BRA│   │NOT│MCT│ \ │   │UP │ + │
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │Mac│L1D│   │LUN│ LION │LOGOS│  \   │CEL│LEF│DOW│RIG│
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */
  [_LOWER] = LAYOUT(
    KC_LPAD, KC_BRID,   KC_BRIU,   WIREVPN_OPEN,   CALCULATOR_OPEN,   MONITOR_OPEN,         ZOOM_OPEN,   KC_F8,   KC_F9,   KC_LCBR,   KC_RCBR, KC_F12,
    SAFARI_OPEN, KC_NO,  KC_NO,  KC_NO,   KC_NO,   TERMINAL_OPEN,         KC_NO,   KC_NO,   KC_NO,   KC_LBRC,  KC_RBRC, KC_DEL,
    KC_CAPS, AWS_SSO, KC_NO, KC_NO, KC_NO, FIREFOX_OPEN,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_EQL,
    KC_LSFT, KC_NO, KC_NO,   KC_NO, KC_NO,  BRAVE_OPEN,       NOTES_OPEN, KC_MCTL, KC_BSLS, KC_NO,  KC_UP, KC_PLUS,
        KC_LGUI, KC_NO, KC_NO, LOGO_LUNCH  ,LOGO_LION , LOGO_SWITCH,      KC_BSLS,   LOGO_CELUS,   KC_LEFT,    KC_DOWN,   KC_RIGHT
        ),
    /*
     * _RAISE
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │LOK│ 1 │ 2 │ 3 │   │   │   │   │   │PRV│PLY│NXT│FIR│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │   │ 4 │ 5 │ 6 │   │   │   │   │   │   │ { │ } │   │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │   │ 7 │ 8 │ 9 │   │VOL+│ │VOL-│ ( │ ) │   │   │ = │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SFT│ . │ 0 │   │   │   │   │   │   │   │   │   │SFT│
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │Mac│ * │ + │ - │   /   │ENT│       │PGU│PGD│L2D│   │
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */

  [_RAISE] = LAYOUT(
        MATTERMOST_OPEN, KC_1, KC_2, KC_3,  KC_NO,  KC_NO,          KC_NO,   KC_NO,   KC_MPRV,   KC_MPLY,   KC_MNXT,   QK_BOOT,
        KC_NO, KC_4,  KC_5,  KC_6,   KC_NO,  KC_NO,          KC_NO,   KC_NO,   KC_NO,   KC_LCBR,   KC_RCBR,   KC_NO,
        KC_NO, KC_7,  KC_8,  KC_9,   KC_NO,  KC_VOLD,        KC_VOLU, KC_LPRN, KC_RPRN, KC_NO, KC_SCLN, KC_EQL,
        KC_LSFT, KC_DOT,  KC_0,  KC_NO,   KC_NO,  KC_NO,          KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO ,   KC_RSFT,
        KC_LGUI, KC_PAST, KC_PLUS,  KC_MINS,    KC_SLSH,       KC_ENT,     KC_NO,    KC_PGUP,   KC_PGDN,   KC_NO,   KC_NO
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
                current_logo = (current_logo + 1) % 8; // Cycle through 0..7
            }
            break;
        case LOGO_LION:
            if (record->event.pressed) {
                current_logo = 1;
            }
            break;
        case LOGO_FLAMENGO:
            if (record->event.pressed) {
                current_logo = 3;
            }
            break;
        case LOGO_BAYERN:
            if (record->event.pressed) {
                current_logo = 2;
            }
            break;
        case LOGO_RIO:
            if (record->event.pressed) {
                current_logo = 5;
            }
            break;
        case LOGO_CELUS:
            if (record->event.pressed) {
                current_logo = 4;
            }
            break;
        case LOGO_THEOFFICE:
            if (record->event.pressed) {
                current_logo = 7;
            }
            break;
        case LOGO_LUNCH:
            if (record->event.pressed) {
                current_logo = 6;
            }
            break;
        case LOGO_TOMORROWLAND:
            if (record->event.pressed) {
                current_logo = 0;
            }
            break;
        case BRAVE_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("Brave Brow");
            }
            return false;
        case ZOOM_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("Zoom");
            }
            return false;
        case NOTES_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("Notes");
            }
            return false;
        case WIREVPN_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("WireGuard");
            }
            return false;
        case SAFARI_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("Safari");
            }
            return false;
        case FIREFOX_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("Firefox");
            }
            return false;
        case MATTERMOST_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("Mattermost");
            }
            return false;
        case CALCULATOR_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("Calculator");
            }
            return false;
        case MONITOR_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("Monit");
            }
            return false;
        case TERMINAL_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("Terminal");
            }
            return false;
        case AWS_SSO:
            if (record->event.pressed) {
                // Fixed smart quotes. Optionally append Enter: SS_TAP(X_ENTER)
                SEND_STRING("aws sso login" SS_TAP(X_ENTER));
            }
            return false;
    }
    return true;
}

// macOS: Open Spotlight, type NAME, press Enter
static void open_using_spotlight(const char *name) {
    tap_code16(G(KC_SPC));
    wait_ms(200);
    send_string_with_delay(name, 0);
    tap_code(KC_ENT);
}

bool oled_task_user(void) {
    // Show layer-specific images; on base layer, honor the selected current_logo
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == _QWERTY) {
        switch (current_logo) {
            case 0: render_tomorrowland(); break;
            case 1: render_lion(); break;
            case 2: render_bayern(); break;
            case 3: render_flamengo(); break;
            case 4: render_celus(); break;
            case 5: render_rio(); break;
            case 6: render_lunch(); break;
            case 7: render_theoffice(); break;
            default: render_tomorrowland(); break;
        }
    } else {
        switch (layer) {
            case _LOWER:
                render_lower();
                break;
            case _RAISE:
                render_raise();
                break;
            case _ADJUST:
                render_rio();
                break;
            default:
                render_celus();
                break;
        }
    }
    return false;
}
