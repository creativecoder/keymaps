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

#ifdef COMBO_ENABLE
#include "g/keymap_combo.h"
#include "combos.h"
#endif

#ifdef ENCODER_ENABLE
#include "encoders.h"
#endif

#ifdef RGBLIGHT_LAYERS
#include "rgb_layers.h"
#endif

#ifdef TAP_DANCE_ENABLE
#include "tapdance.h"
#endif

#ifdef OLED_ENABLE
#include "oled.h"
#endif

#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used

#define U_RDO SCMD(KC_Z)
#define U_PST LCMD(KC_V)
#define U_CPY LCMD(KC_C)
#define U_CUT LCMD(KC_X)
#define U_UND LCMD(KC_Z)
#define EMICONS LCTL(LGUI(KC_E))
#define SCRNSHT LSG(KC_4)
#define SCRNCLP C(LSG(KC_4))
#define SCRNREC LSG(KC_5)
#define CLIPBRD LAG(KC_BSLS)
#define SNIPS LCAG(KC_SPC)

enum custom_keycodes {
    CPY_URL = SAFE_RANGE,
    CPY_GO,
    QT_RPLY,
    VIM_WQ,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_kyria_3x5(
      TD(Q_CTRL),        KC_W,              KC_F,              KC_P,              KC_B,                                                                                           KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,
      LCTL_T(KC_A),      LALT_T(KC_R),      LGUI_T(KC_S),      LSFT_T(KC_T),      KC_G,                                                                                           KC_M,              RSFT_T(KC_N),      RGUI_T(KC_E),      RALT_T(KC_I),      RCTL_T(KC_O),
      KC_Z,              ALGR_T(KC_X),      KC_C,              KC_D,              KC_V,              LT(FUN, KC_DEL),   LT(SYM, KC_ENT),    LT(SHCTS, KC_TAB), LT(MEDIA, KC_ESC), KC_K,              KC_H,              KC_COMM,           KC_DOT,            KC_SLSH,
                                            KC_ENT,            LT(MEDIA, KC_ESC), LT(NAV, KC_SPC),   LT(SHCTS, KC_TAB), LT(NUM, KC_BSPC),   LT(NAV, KC_SPC),   LT(SYM, KC_ENT),   LT(NUM, KC_BSPC),  LT(FUN, KC_DEL),   KC_ENT
    ),
    [NAV] = LAYOUT_kyria_3x5(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_CAPS,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    U_NU,    KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,
                        U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    KC_ENT,  KC_BSPC, KC_DEL,  U_NU
    ),
    [SHCTS] = LAYOUT_kyria_3x5(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        U_NU,    U_NU,    U_NU,    U_NU,    CLIPBRD,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        KC_SPC,  CPY_URL, CPY_GO,  QT_RPLY, VIM_WQ,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    U_NU,    EMICONS, SCRNSHT, SCRNCLP, SCRNREC, SNIPS,
                        U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    KC_ENT,  KC_BSPC, KC_DEL,  U_NU
    ),
    [MEDIA] = LAYOUT_kyria_3x5(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, VIM_WQ,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,
                        U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    KC_MSTP, KC_MPLY, KC_MUTE, KC_MUTE
    ),
    [NUM] = LAYOUT_kyria_3x5(
      KC_PERC, KC_7,    KC_8,    KC_9,    KC_SLSH,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
      KC_EQL,  KC_4,    KC_5,    KC_6,    KC_ASTR,                                     U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      KC_DOT,  KC_1,    KC_2,    KC_3,    KC_PLUS, U_NU,    U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                        U_NU,    KC_GRV,  KC_0,    KC_MINS, U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU
    ),
    [SYM] = LAYOUT_kyria_3x5(
      KC_PIPE, KC_AMPR, KC_LCBR, KC_RCBR, KC_BSLS,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
      KC_SCLN, KC_COLN, KC_LPRN, KC_RPRN, KC_AT,                                       U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      KC_DLR,  KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, U_NU,    U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                        U_NU,    KC_HASH, KC_EXLM, KC_UNDS, U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU
    ),
    [FUN] = LAYOUT_kyria_3x5(
      KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
      KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_PAUS,                                     U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_SLCK, U_NU,    U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                        U_NU,    KC_APP,  KC_SPC,  KC_TAB,  U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU
    ),
    [MOUSE] = LAYOUT_kyria_3x5(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, U_NU,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    U_NU,    KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, U_NU,
                        U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    KC_BTN1, KC_BTN3, KC_BTN2, U_NU
    ),
    [MBO] = LAYOUT_kyria_3x5(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_TRNS,                                     KC_TRNS, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   U_NU,    U_NU,    U_NU,    U_NU,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
                        U_NU,    KC_BTN2, KC_BTN3, KC_BTN1, U_NU,    U_NU,    KC_BTN1, KC_BTN3, KC_BTN2, U_NU
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();

    switch (keycode) {
        case CPY_URL:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
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
                    del_mods(mod_state);
                    register_code(KC_LGUI);
                    tap_code(KC_L);
                    tap_code(KC_C);
                    unregister_code(KC_LGUI);
                    tap_code(KC_ESC);
                    set_mods(mod_state);
                }
            }
            return false;
        case CPY_GO:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    del_mods(mod_state);
                    tap_code16(U_CPY);
                    tap_code(KC_LCTL);
                    SEND_STRING(SS_DELAY(200) SS_TAP(X_TAB) "ddg");
                    tap_code(KC_ENT);
                    set_mods(mod_state);
                } else {
                    del_mods(mod_state);
                    tap_code16(U_CPY);
                    tap_code(KC_LCTL);
                    SEND_STRING(SS_DELAY(200));
                    tap_code(KC_ENT);
                    set_mods(mod_state);
                }
            }
            return false;
        case QT_RPLY:
            if (record->event.pressed) {
                del_mods(mod_state);
                tap_code16(U_CPY);
                tap_code16(KC_GT);
                tap_code16(U_PST);
                SEND_STRING(SS_DELAY(200));
                tap_code16(S(KC_ENT));
                tap_code16(LSG(KC_9));
                set_mods(mod_state);
            }
            return false;
        case VIM_WQ:
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
