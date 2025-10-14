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
    LOGO_DJ,
    PASSW_GEN_TYPE,
    BRAVE_OPEN,
    ZOOM_OPEN,
    TXTEDIT_OPEN,
    WIREVPN_OPEN,
    SAFARI_OPEN,
    FIREFOX_OPEN,
    MATTERMOST_OPEN,
    CALCULATOR_OPEN,
    MONITOR_OPEN,
    AWS_SSO,
    TERMINAL_OPEN,
    SPOTIFY_OPEN,
    VIM_TYPE,
    KUBECTL_TYPE,
    K8SCNTX_TYPE,
    TERRAFORM_TYPE,
    K9S_OPEN,
    GIT_TYPE,
    EDGE_OPEN,
    CODE_OPEN,
    VIM_WQ_TYPE,
    GIT_CLONE_TYPE,
    COMET_OPEN,
    LOCK_SCREEN,
    APPLE_AI
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
     * │TAB│ Q │ Y*│ E │ R │ T │   │ W │ U │ I │ O │ P |BSP│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │ ; │ A │ S │ D │ F │ '*│   │ H │ J*│ K │ L │ ` │ - │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SFT│ G │ Z │ X │ C │ V │   │ B │ N │ M │ / │ = │SFT│
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │Mac│CTL│OPT│L1 │ Apps  │SPC│ ENTER │ L2│ , │ | │ . │
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     *  ' andd Y and J have been swapped to optimize faildure key positions
     */
  [_QWERTY] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4, KC_5,           KC_6,   KC_7, KC_8,    KC_9,    KC_0, KC_KB_MUTE,
        KC_TAB,  KC_Q,    KC_Y,    KC_E,    KC_R, KC_T,           KC_W,   KC_U, KC_I,    KC_O,    KC_P, KC_BSPC,
        KC_SCLN, KC_A,    KC_S,    KC_D,   KC_F, KC_QUOT,           KC_H,   KC_J, KC_K,    KC_L,    KC_GRV,  KC_MINS,
        KC_LSFT,   KC_G,     KC_Z,    KC_X,    KC_C, KC_V,           KC_B,   KC_N, KC_M, KC_SLSH,  KC_EQL, KC_RSFT,
        KC_LGUI, KC_LCTL, KC_LOPT, MO(1), KC_LPAD ,          KC_SPC      ,  KC_ENT, MO(2),  KC_COMM,   KC_PIPE, KC_DOT
        ),
    /*
     * LOWER
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │LOK│BRV│CMT│VPN│CAL│CPU│   │ZOM│VSC│TXT│ { │ } │F12│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │MCL│VWQ│   │   │RIO│TER│   │ Y │   │ J │ [ │ ] │DEL│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │   │   │ Y │   │   │   │   │ F │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SFT│ Z │   │   │   │ ' │   │   │ J │   │ \ │U^P│SFT│
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │Mac│CAP│LUN│L1D│ LION │LOGOS│CELUS │   │LEF│DOW│RIG│
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */
  [_LOWER] = LAYOUT(
    LOCK_SCREEN, BRAVE_OPEN,   COMET_OPEN,   WIREVPN_OPEN,   CALCULATOR_OPEN,   MONITOR_OPEN,         ZOOM_OPEN,   CODE_OPEN,   TXTEDIT_OPEN,   KC_LCBR,   KC_RCBR, KC_F12,
    KC_MCTL, VIM_WQ_TYPE,  KC_NO,  KC_NO,   LOGO_RIO,   TERMINAL_OPEN,         KC_Y,   KC_NO,   KC_J,   KC_LBRC,  KC_RBRC, KC_DEL,
    KC_NO, KC_NO, KC_Y, KC_NO, KC_U, KC_NO,       KC_F, KC_NO, KC_P, KC_NO, KC_NO, KC_NO,
    KC_LSFT, KC_Z, KC_NO,   KC_NO, KC_NO,  KC_QUOT,       KC_NO, KC_J, KC_NO, KC_BSLS,  KC_UP, KC_RSFT,
        KC_LGUI, KC_CAPS, LOGO_LUNCH, KC_NO, LOGO_LION , LOGO_SWITCH,      LOGO_CELUS,   KC_NO,   KC_LEFT,    KC_DOWN,   KC_RIGHT
        ),
    /*
     * _RAISE
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │LOK│SAF│CMT│BRV│FRX│EDG│   │   │   │PWD│K9S│SPO│FIR│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │AAI│   │   │   │   │TFP│   │   │   │ Y │PRV│PLY│NXT│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │AWS│SPO│   │   │   │   │   │FRX│   │K8S│GTC│   │   │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SFT│GIT│   │   │KCX│   │   │   │   │   │ \ │UP │SFT│
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │Mac│   │VO+│VO-│ SPOT │LOGOS│ ENTER│L2D│LEF│DOW│RIG│
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */

  [_RAISE] = LAYOUT(
        LOCK_SCREEN, SAFARI_OPEN, COMET_OPEN, BRAVE_OPEN,  FIREFOX_OPEN,  EDGE_OPEN,          KC_NO,   KC_NO,   PASSW_GEN_TYPE,   K9S_OPEN,   SPOTIFY_OPEN,   QK_BOOT,
        APPLE_AI, KC_NO,  KC_NO,  VIM_TYPE,   KC_NO,  TERRAFORM_TYPE,          KC_Y,   KC_NO,   KC_Y,    KC_MPRV,   KC_MPLY,   KC_MNXT,
        KC_NO,  AWS_SSO,  SPOTIFY_OPEN, KC_NO,   KC_NO,  KC_NO,        FIREFOX_OPEN, KC_NO, KUBECTL_TYPE,  GIT_CLONE_TYPE, KC_NO, KC_NO,
        KC_LSFT, GIT_TYPE,  KC_NO,  KC_NO,   K8SCNTX_TYPE,  KC_NO,          KC_NO,   KC_NO,   KC_NO,   KC_BSLS,  KC_UP ,   KC_RSFT,
        KC_LGUI, KC_NO, KC_KB_VOLUME_UP,  KC_KB_VOLUME_DOWN,    SPOTIFY_OPEN,       LOGO_SWITCH,     KC_ENT, KC_NO,   KC_LEFT,    KC_DOWN,   KC_RIGHT
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
    [_LOWER]  = { ENCODER_CCW_CW(KC_BRIGHTNESS_UP, KC_BRIGHTNESS_DOWN)  },
    [_RAISE]  = { ENCODER_CCW_CW(KC_DOWN, KC_UP)  },
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
        case LOGO_DJ:
            if (record->event.pressed) {
                current_logo = 8;
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
        case TXTEDIT_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("TextEdit");
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
        case SPOTIFY_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("Spotify");
            }
            return false;
        case AWS_SSO:
            if (record->event.pressed) {
                SEND_STRING("aws sso login" SS_TAP(X_ENTER));
            }
            return false;
        case VIM_TYPE:
            if (record->event.pressed) {
                SEND_STRING("vim ");
            }
            return false;
        case KUBECTL_TYPE:
            if (record->event.pressed) {
                SEND_STRING("kubectl ");
            }
            return false;
        case K8SCNTX_TYPE:
            if (record->event.pressed) {
                SEND_STRING("kubectl config use-context site-");
            }
            return false;
        case TERRAFORM_TYPE:
            if (record->event.pressed) {
                SEND_STRING("terraform plan ");
            }
            return false;
        case K9S_OPEN:
            if (record->event.pressed) {
                SEND_STRING("k9s" SS_TAP(X_ENTER));
            }
            return false;
        case GIT_TYPE:
            if (record->event.pressed) {
                SEND_STRING("git commit --amend");
            }
            return false;
        case EDGE_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("Microsoft Edge");
            }
            return false;
        case CODE_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("Code");
            }
            return false;
        case VIM_WQ_TYPE:
            if (record->event.pressed) {
                SEND_STRING(":wq");
            }
            return false;
        case GIT_CLONE_TYPE:
            if (record->event.pressed) {
                // Requires envirohment variables gusr and tok to your git username and personal access token respectively
                SEND_STRING("git clone https://$gusr:$tok@git.celus.co ");
            }
            return false;
        case COMET_OPEN:
            if (record->event.pressed) {
                open_using_spotlight("Comet");
            }
            return false;
            // Lock screen (macOS) using Control-Command-Q: Immediately lock your screen
        case LOCK_SCREEN:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LGUI("q")));
            }
            return false;
            // Open Apple Intelligence (macOS) using Command double tap
        case APPLE_AI:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LGUI()));
            }
            return false;
            // Random password generator makes random 23 characters
        case PASSW_GEN_TYPE:
            if (record->event.pressed) {
                {   static bool seeded = false;
                    if (!seeded) {
                        srand(timer_read()); // simple seed
                        seeded = true;
                    }
                    static const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
                    char pw[24]; // 23 chars + null
                    for (uint8_t i = 0; i < 23; i++) {
                        pw[i] = charset[rand() % (sizeof(charset) - 1)];
                    }
                    pw[23] = '\0';
                    send_string(pw); // types the password
                    current_logo = 9;
                }
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
    // Enter not working with tap_code16 for some reason since MacOS 26
    // tap_code(KC_ENTER);
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
            case 8: render_dj(); break;
            case 9: render_passwgen(); break;
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
