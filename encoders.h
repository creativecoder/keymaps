/* Copyright 2021 Grant M. Kinney
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

bool encoder_update_user(uint8_t index, bool ccw) {
    mod_state = get_mods();
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case NUM:
            case SYM:
                // Select next/previous window
                if (ccw) {
                    tap_code16(LSG(KC_GRV));
                } else {
                    tap_code16(LGUI(KC_GRV));
                }
                break;
            case FUN:
                // Brightness up/down
                if (ccw) {
                    tap_code(KC_BRID);
                } else {
                    tap_code(KC_BRIU);
                }
                break;
            default:
                // Select next/previous application
                if (!is_app_switcher_active) {
                    is_app_switcher_active = true;
                    register_code(KC_LGUI);
                }
                if (ccw) {
                    tap_code16(S(KC_TAB));
                } else {
                    tap_code16(KC_TAB);
                }
                app_switcher_timer = timer_read();
                break;

        }
    }
    else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case SCUTS:
            case NAV:
                // Select next/previous tab
                if (ccw) {
                    tap_code16(LSG(KC_LBRC));
                } else {
                    tap_code16(LSG(KC_RBRC));
                }
                break;
            case MEDIA:
                // Volume control
                if (ccw) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
                break;
            case MOUSE:
                // Mouse scroll up/down
                if (ccw) {
                    tap_code(KC_WH_D);
                } else {
                    tap_code(KC_WH_U);
                }
                break;
            default:
                // Scrolling with Page up/Page down
                if (get_mods() && MOD_MASK_CTRL) {
                    del_mods(mod_state);
                    if (ccw) {
                        tap_code(KC_UP);
                    } else {
                        tap_code(KC_DOWN);
                    }
                    set_mods(mod_state);
                } else {
                    if (ccw) {
                        tap_code(KC_PGUP);
                    } else {
                        tap_code(KC_PGDN);
                    }
                }
                break;

        }
    }
    return false;
}

void matrix_scan_user(void) {
    if (is_app_switcher_active && timer_elapsed(app_switcher_timer) > 1000) {
        unregister_code(KC_LGUI);
        is_app_switcher_active = false;
        app_switcher_timer = 0;
    }
}
