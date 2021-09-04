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

// Tap Dance keycodes
enum td_keycodes {
    Q_CTRL // "q" when tapped, tap Ctrl when double tapped
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [Q_CTRL] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_LCTL),
};
