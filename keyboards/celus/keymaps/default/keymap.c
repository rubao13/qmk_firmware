// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H
#include "lib/logos.h"
#include "lib/wpm.h"
#include "secrets.h"
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

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_LOWER]  = { ENCODER_CCW_CW(KC_BRIGHTNESS_UP, KC_BRIGHTNESS_DOWN)  },
    [_RAISE]  = { ENCODER_CCW_CW(KC_DOWN, KC_UP)  },
    [_ADJUST] = { ENCODER_CCW_CW(KC_NO, KC_NO) },
};
#endif

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
    APPLE_AI,
    CMD_TAB,
    BITWARDEN_UNLOCK,
    CMD_Q,
    SCREENSHOT,
    K9S_CTX_TYPE,
    K9S_NS_TYPE,
    CMD_SAVE,
    TYPE_EMAIL_WORK,
    TYPE_EMAIL_GMAIL,
    TYPE_EMAIL_DEUTSCH,
    CMD_V,
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
     * │ ; │ A │ S │ D │ F │ G │   │ H │ J │ K │ L │ , │ . │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SFT│ ' │ Z │ X │ C │ V │   │ B │ N │ M │ ` │ ↑ │ - │
     * ├───┼───┼───┼───┼───┴───┼───┴───┴───┼───┼───┼───┼───┤
     * │ / │CTL│OPT│L1 │  Mac  │   SPACE   │ L2│ ← │ ↓ │ → │
     * └───┴───┴───┴───┴───────┴───────┴───┴───┴───┴───┴───┘
     */
  [_QWERTY] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4, KC_5, /* SPACE */ KC_6,   KC_7, KC_8,    KC_9,    KC_0, KC_KB_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R, KC_T, /* SPACE */ KC_Y,   KC_U, KC_I,    KC_O,    KC_P, KC_BSPC,
        KC_SCLN, KC_A,    KC_S,    KC_D,    KC_F, KC_G, /* SPACE */ KC_H,   KC_J, KC_K,    KC_L,    KC_COMM,  KC_DOT,
        KC_LSFT,   KC_QUOT, KC_Z,  KC_X,    KC_C, KC_V, /* SPACE */ KC_B,   KC_N, KC_M, KC_GRV,  KC_UP, KC_MINS,
        KC_SLSH, KC_LCTL, KC_LOPT, MO(1),     KC_LGUI,    KC_SPC,   KC_SPC, MO(2),  KC_LEFT,   KC_DOWN, KC_RIGHT
        ),
    /*
     * LOWER
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │LOK│CEL│EMC│EMG│EMD│SHT│   │ZOM│VSC│TXT│ { │ } │F12│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │MCL│VWQ│   │   │RIO│KXT│   │   │   │   │ [ │ ] │DEL│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │   │   │SAV│   │   │GIT│   │   │   │   │LIO│   │   │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SFT│   │MTb│CQT│LOK│PST│   │BUL│KNS│   │   │DEL│ = │
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │ \ │CAP│LUN|L1D│  Mac │LOGOS│ENTER │   │   │ | │   │
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */
  [_LOWER] = LAYOUT(
    LOCK_SCREEN, LOGO_CELUS, TYPE_EMAIL_WORK, TYPE_EMAIL_GMAIL, TYPE_EMAIL_DEUTSCH, SCREENSHOT, /* SPACE */ ZOOM_OPEN,   CODE_OPEN,   TXTEDIT_OPEN,   KC_LCBR,   KC_RCBR, KC_F12,
    
    KC_MCTL, VIM_WQ_TYPE, KC_NO,  KC_NO, LOGO_RIO, K9S_CTX_TYPE, /* SPACE */ KC_NO,   KC_NO,   KC_NO,   KC_LBRC,  KC_RBRC, KC_DEL,
    
    KC_NO, AWS_SSO, CMD_SAVE, KC_NO, KC_NO, GIT_TYPE, /* SPACE */ KC_NO, KC_NO, KC_NO, LOGO_LION, KC_NO, KC_NO,
    
    KC_LSFT, KC_NO, CMD_TAB, CMD_Q, LOCK_SCREEN, CMD_V, /* SPACE */ BITWARDEN_UNLOCK, K9S_NS_TYPE, LOGO_LUNCH, KC_NO,  KC_DEL, KC_EQL,
    
    KC_BSLS, KC_CAPS,LOGO_LUNCH, KC_NO,KC_LGUI , LOGO_SWITCH,KC_ENT,   KC_NO,   KC_NO,    KC_PIPE,   KC_NO
        ),
    /*
     * _RAISE
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │LOK│SAF│CMT│BRV│FRX│EDG│   │   │   │PWD│K9S│SPO│FIR│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │AAI│   │   │   │   │TFP│   │   │   │   │PRV│PLY│NXT│
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │   │AWS│SPO│   │   │GCL│   │FRX│   │K8S│LOK│   │   │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │SFT│   │   │   │KCX│VIM│   │BUL│   │   │   │DEL│ = │
     * ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
     * │   │   │OPT│   │  Mac │LOGOS│ ENTER│L2D│   │ | │   │
     * └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
     */

  [_RAISE] = LAYOUT(
        LOCK_SCREEN, SAFARI_OPEN, COMET_OPEN, BRAVE_OPEN,  FIREFOX_OPEN,  EDGE_OPEN, /* SPACE */ KC_NO,   KC_NO,   PASSW_GEN_TYPE,   K9S_OPEN,   SPOTIFY_OPEN,   QK_BOOT,
        
        APPLE_AI, KC_NO, KC_NO, KC_NO, KC_NO, TERRAFORM_TYPE, /* SPACE */ KC_NO,   KC_NO,   KC_NO,    KC_MPRV,   KC_MPLY,   KC_MNXT,
        
        KC_NO,  AWS_SSO, SPOTIFY_OPEN, KC_NO, KC_NO,GIT_CLONE_TYPE, /* SPACE */ FIREFOX_OPEN, KC_NO, KUBECTL_TYPE,  LOCK_SCREEN, KC_NO, KC_NO,
        
        KC_LSFT, KC_NO, KC_NO,  KC_NO, K8SCNTX_TYPE, VIM_TYPE, /* SPACE */ BITWARDEN_UNLOCK,   KC_NO,   KC_NO,   KC_NO,  KC_DEL ,   KC_EQL,
        
        KC_NO, KC_NO, KC_LOPT,  KC_NO, KC_LGUI, LOGO_SWITCH, KC_ENT, KC_NO,   KC_NO,    KC_PIPE,   KC_NO
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
                tap_code(KC_LGUI);
                wait_ms(75); // brief pause so macOS registers the double tap
                tap_code(KC_LGUI);
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
        case CMD_TAB:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code(KC_TAB);
                unregister_code(KC_LGUI);
            }
            return false;
        // in the browser bitwarden shortcut to unlock is Cmd+Shift+L
        case BITWARDEN_UNLOCK:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LSFT("l")));
            }
            return false;
        // Cmd+Q to quit apps on macOS
        case CMD_Q:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("q"));
            }
            return false;
        // Screenshot on macOS Cmd+Shift+5
        case SCREENSHOT:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LSFT("5")));
            }
            return false;
        case K9S_CTX_TYPE:
            if (record->event.pressed) {
                SEND_STRING(":ctx");
            }
            return false;
        case K9S_NS_TYPE:
            if (record->event.pressed) {
                SEND_STRING(":ns");
            }
            return false;
        case CMD_SAVE:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("s"));
            }
            return false;
        case TYPE_EMAIL_WORK:
            if (record->event.pressed) {
                SEND_STRING(EMAIL_WORK);
            }
            return false;
        case TYPE_EMAIL_GMAIL:
            if (record->event.pressed) {
                SEND_STRING(EMAIL_GMAIL);
            }
            return false;
        case TYPE_EMAIL_DEUTSCH:
            if (record->event.pressed) {
                SEND_STRING(EMAIL_DEUTSCH);
            }
            return false;
        case CMD_V:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("v"));
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
