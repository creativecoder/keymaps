/* Copyright 2021 Grant M. Kinney
 *
 * Based on the Miryoku layout by Manna Harbour
 * https://github.com/manna-harbour/miryoku
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

enum layers { BASE, FUN, MBO, MEDIA, MOUSE, NAV, NUM, SHCTS, SYM };

// Initialize variable holding the binary representation of active modifiers.
uint8_t mod_state;

#include "layout.h"

#include "casemodes.h"  // https://github.com/andrewjrae/kyria-keymap#case-modes

#ifdef COMBO_ENABLE
#    include "g/keymap_combo.h"
#    include "combos.h"
#endif

#ifdef ENCODER_ENABLE
#    include "encoders.h"
#endif

#ifdef RGBLIGHT_LAYERS
#    include "rgb_layers.h"
#endif

#ifdef TAP_DANCE_ENABLE
#    include "tapdance.h"
#endif

#ifdef OLED_ENABLE
#    include "oled.h"
#endif

#define U_NA KC_NO  // present but not available for use
#define U_NU KC_NO  // available but not used

#define U_RDO SCMD(KC_Z)
#define U_PST LCMD(KC_V)
#define U_CPY LCMD(KC_C)
#define U_CUT LCMD(KC_X)
#define U_UND LCMD(KC_Z)
#define EMICONS LCTL(LCAG(KC_E))
#define SCRNSHT LSG(KC_4)
#define SCRNCLP C(LSG(KC_4))
#define SCRNREC LSG(KC_5)
#define CLIPBRD LAG(KC_BSLS)
#define SNIPS LCAG(KC_SPC)

enum custom_keycodes {
    CAPSWRD = SAFE_RANGE,
    CPY_URL,
    CPY_GO,
    CPY_SRH,
    QT_RPLY,
    VIM_WQ,
    XCASE,
};

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_kyria_3x5(
      TD(Q_CTRL),        KC_W,              KC_F,              KC_P,              KC_B,                                                                                           KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,
      LCTL_T(KC_A),      LALT_T(KC_R),      LGUI_T(KC_S),      LSFT_T(KC_T),      KC_G,                                                                                           KC_M,              RSFT_T(KC_N),      RGUI_T(KC_E),      RALT_T(KC_I),      RCTL_T(KC_O),
      KC_Z,              ALGR_T(KC_X),      KC_C,              KC_D,              KC_V,              LT(FUN, KC_DEL),   LT(SYM, KC_ENT),    LT(SHCTS, KC_TAB), LT(MEDIA, KC_ESC), KC_K,              KC_H,              KC_COMM,           KC_DOT,            KC_SLSH,
                                            KC_ENT,            LT(MEDIA, KC_ESC), LT(NAV, KC_SPC),   LT(SHCTS, KC_TAB), LT(NUM, KC_BSPC),   LT(NAV, KC_SPC),   LT(SYM, KC_ENT),   LT(NUM, KC_BSPC),  LT(FUN, KC_LSFT),  KC_ENT
    ),
    [NAV] = LAYOUT_kyria_3x5(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        CAPSWRD, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_TAB,  KC_ESC,  XCASE,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                        U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    KC_SPC,  KC_ENT,  KC_DEL,  KC_BSPC, U_NU
    ),
    [SHCTS] = LAYOUT_kyria_3x5(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        U_NU,    U_NU,    U_NU,    QT_RPLY, CLIPBRD,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        KC_SPC,  CPY_URL, CPY_GO,  CPY_SRH, VIM_WQ,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_TAB,  KC_ESC,  EMICONS, SCRNSHT, SCRNCLP, SCRNREC, SNIPS,
                        U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    KC_SPC,  KC_ENT,  KC_DEL,  KC_BSPC, U_NU
    ),
    [MEDIA] = LAYOUT_kyria_3x5(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        U_NU,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,
                        U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    KC_MSTP, KC_MPLY, KC_MUTE, KC_MUTE
    ),
    [NUM] = LAYOUT_kyria_3x5(
      KC_CIRC, KC_7,    KC_8,    KC_9,    KC_SLSH,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
      KC_EQL,  KC_1,    KC_2,    KC_3,    KC_ASTR,                                     U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      KC_DOT,  KC_4,    KC_5,    KC_6,    KC_PLUS, KC_SPC,  U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                        U_NU,    KC_EXLM, KC_0,    KC_MINS, U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU
    ),
    [SYM] = LAYOUT_kyria_3x5(
      KC_TILD, KC_LCBR, KC_RCBR, KC_AMPR, KC_BSLS,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
      KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN, KC_AT,                                       U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      KC_PERC, KC_LBRC, KC_RBRC, KC_DLR,  KC_PIPE, U_NU,    U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                        U_NU,    KC_HASH, KC_GRV,  KC_UNDS, U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU
    ),
    [FUN] = LAYOUT_kyria_3x5(
      KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS,                                     U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      KC_F10,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK, KC_DEL,  KC_ENT,  U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                        U_NU,    KC_APP,  KC_SPC,  KC_TAB,  KC_BSPC, U_NA,    U_NA,    U_NA,    U_NA,    U_NU
    ),
    [MOUSE] = LAYOUT_kyria_3x5(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        U_NU,    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    U_NU,    U_NU,    KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R,
                        U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    KC_BTN1, KC_BTN3, KC_BTN2, U_NU
    ),
    [MBO] = LAYOUT_kyria_3x5(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_TRNS,                                     KC_TRNS, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   U_NU,    U_NU,    U_NU,    U_NU,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
                        U_NU,    KC_BTN2, KC_BTN3, KC_BTN1, U_NU,    U_NU,    KC_BTN1, KC_BTN3, KC_BTN2, U_NU
    ),
};

// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Process case modes
    if (!process_case_modes(keycode, record)) {
        return false;
    }

    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();

    switch (keycode) {
        // Mod-tap keys
        case LT(FUN, KC_LSFT):
            if (record->tap.count && record->event.pressed) {
                // Disable one shot shift if already on, otherwise enable it
                if (get_oneshot_mods() & MOD_MASK_SHIFT) {
                    del_oneshot_mods(MOD_BIT(KC_LSFT));
                } else {
                    set_oneshot_mods(MOD_BIT(KC_LSFT));
                }
                return false;
            }
            return true;

        // Casemodes
        case CAPSWRD:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code(KC_CAPSLOCK);
                    return true;
                } else {
                    enable_caps_word();
                }
            }
            return false;
        case XCASE:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    enable_caps_word();
                }

                if ((get_mods() & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {
                    // CamelCase
                    enable_xcase_with(OSM(MOD_LSFT));
                } else if (get_mods() & MOD_MASK_GUI) {
                    // kebab-case
                    enable_xcase_with(KC_MINS);
                } else {
                    // snake_case
                    enable_xcase_with(KC_UNDS);
                }
            }
            return false;

        // Custom keycodes
        case CPY_URL:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    // Copy current url in browser and open in a new tab
                    // Temporarily cancel existing modifiers, including both shifts
                    del_mods(mod_state);
                    register_code(KC_LGUI);
                    tap_code(KC_L);
                    tap_code(KC_C);
                    tap_code(KC_T);
                    tap_code(KC_V);
                    unregister_code(KC_LGUI);
                    tap_code(KC_ENT);
                    // Reapplying modifier state so that the held shift key(s) still work
                    set_mods(mod_state);
                } else {
                    // Copy current browser url to clipboard
                    del_mods(mod_state);
                    register_code(KC_LGUI);
                    tap_code(KC_L);
                    tap_code(KC_C);
                    unregister_code(KC_LGUI);
                    SEND_STRING(SS_DELAY(100));
                    tap_code(KC_ESC);
                    set_mods(mod_state);
                }
            }
            return false;
        case CPY_GO:
            if (record->event.pressed) {
                // Paste currently highlighted text in browser into a new tab
                del_mods(mod_state);
                register_code(KC_LGUI);
                tap_code(KC_C);
                tap_code(KC_T);
                tap_code(KC_V);
                unregister_code(KC_LGUI);
                tap_code(KC_ENT);
                set_mods(mod_state);
            }
            return false;
        case CPY_SRH:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    // Use Launchbar to search web for highlighted text
                    del_mods(mod_state);
                    tap_code16(U_CPY);
                    tap_code(KC_LCTL);
                    SEND_STRING(SS_DELAY(200));
                    tap_code(KC_ENT);
                    set_mods(mod_state);
                } else {
                    // Use Launchbar to go to highlighted url
                    del_mods(mod_state);
                    tap_code16(U_CPY);
                    tap_code(KC_LCTL);
                    SEND_STRING(SS_DELAY(200) SS_TAP(X_TAB) "ddg");
                    tap_code(KC_ENT);
                    set_mods(mod_state);
                }
            }
            return false;
        case QT_RPLY:
            // Quote highlighted text and start a reply in Slack
            if (record->event.pressed) {
                del_mods(mod_state);
                tap_code16(U_CPY);
                SEND_STRING(SS_DELAY(200));
                tap_code16(KC_GT);
                SEND_STRING(SS_DELAY(200));
                tap_code16(U_PST);
                SEND_STRING(SS_DELAY(200));
                tap_code16(S(KC_ENT));
                tap_code16(LSG(KC_9));
                set_mods(mod_state);
            }
            return false;
        case VIM_WQ:
            // Save changes and quit vim
            if (record->event.pressed) {
                del_mods(mod_state);
                tap_code(KC_ESC);
                SEND_STRING(":wq");
                tap_code(KC_ENT);
                set_mods(mod_state);
            }
            return false;
    }
    return true;
};
