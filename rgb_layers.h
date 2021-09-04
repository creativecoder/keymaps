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

const rgblight_segment_t PROGMEM capslock_layer_led[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_RED},      // Light 3 LEDs, starting with LED 0
    {8, 3, HSV_RED}       // Light 3 LEDs, starting with LED 8 (1st LED on 2nd half)
);

const rgblight_segment_t PROGMEM nav_layer_led[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 3, HSV_MAGENTA},  // Light the last 3 LEDs on the 1st half
    {13, 3, HSV_MAGENTA}  // Lighe the last 3 LEDs on the 2nd half
);

const rgblight_segment_t PROGMEM shortcuts_layer_led[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 3, HSV_GREEN},
    {13, 3, HSV_GREEN}
);

const rgblight_segment_t PROGMEM media_layer_led[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 3, HSV_YELLOW},
    {13, 3, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM mouse_layer_led[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 3, HSV_TEAL},
    {13, 3, HSV_TEAL}
);

const rgblight_segment_t PROGMEM num_layer_led[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 3, HSV_BLUE},
    {13, 3, HSV_BLUE}
);

const rgblight_segment_t PROGMEM sym_layer_led[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 3, HSV_PURPLE},
    {13, 3, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM fun_layer_led[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 3, HSV_ORANGE},
    {13, 3, HSV_ORANGE}
);

// Now define the array of layers. Later layers take precedence.
const rgblight_segment_t* const PROGMEM kyria_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    capslock_layer_led,
    nav_layer_led,
    shortcuts_layer_led,
    media_layer_led,
    mouse_layer_led,
    num_layer_led,
    sym_layer_led,
    fun_layer_led
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = kyria_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, NAV));
    rgblight_set_layer_state(2, layer_state_cmp(state, SHCTS));
    rgblight_set_layer_state(3, layer_state_cmp(state, MEDIA));
    rgblight_set_layer_state(4, layer_state_cmp(state, MOUSE));
    rgblight_set_layer_state(5, layer_state_cmp(state, NUM));
    rgblight_set_layer_state(6, layer_state_cmp(state, SYM));
    rgblight_set_layer_state(7, layer_state_cmp(state, FUN));
    return state;
}
