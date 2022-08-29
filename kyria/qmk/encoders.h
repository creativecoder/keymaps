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

bool encoder_update_user(uint8_t index, bool clockwise) {
    mod_state = get_mods();
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case NUM:
                // Select next/previous window
                if (clockwise) {
                    tap_code16(LCTL(KC_GRV));
                } else {
                    tap_code16(S(LCTL(KC_GRV)));
                }
                break;
            case FUN:
                // Brightness up/down
                if (clockwise) {
                    tap_code(KC_BRIU);
                } else {
                    tap_code(KC_BRID);
                }
                break;
            default:
                if (clockwise) {
                    tap_code(KC_TAB);
                } else {
                    tap_code16(S(KC_TAB));
                }
                break;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case NAV:
            case SHCTS:
                // Select next/previous tab
                if (clockwise) {
                    tap_code16(S(LCTL(KC_RBRC)));
                } else {
                    tap_code16(S(LCTL(KC_LBRC)));
                }
                break;
            case MEDIA:
                // Volume control
                if (clockwise) {
                    tap_code(KC__VOLUP);
                } else {
                    tap_code(KC__VOLDOWN);
                }
                break;
            case MOUSE:
                // Mouse scroll up/down
                if (clockwise) {
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
                break;
            default:
                // Scrolling with Page up/Page down
                if (get_mods() && MOD_MASK_CTRL) {
                    del_mods(mod_state);
                    if (clockwise) {
                        tap_code(KC_DOWN);
                    } else {
                        tap_code(KC_UP);
                    }
                    set_mods(mod_state);
                } else {
                    if (clockwise) {
                        tap_code(KC_PGDN);
                    } else {
                        tap_code(KC_PGUP);
                    }
                }
                break;
        }
    }
    return false;
}
