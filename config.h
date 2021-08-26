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

#pragma once

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

// Auto Shift
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define AUTO_SHIFT_NO_SETUP

// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 4

#ifdef COMBO_ENABLE
    #define COMBO_TERM 20
    #define COMBO_STRICT_TIMER
    #define COMBO_MUST_TAP_PER_COMBO
#endif

#ifdef ENCODER_ENABLE
    // Alps EC11K1524406 encoder uses a smaller resolution
    #define ENCODER_RESOLUTION 2
#endif

#ifdef MOUSEKEY_ENABLE
    // Mouse key speed and acceleration.
    #define MOUSEKEY_DELAY          0
    #define MOUSEKEY_INTERVAL       16
    #define MOUSEKEY_WHEEL_DELAY    0
    #define MOUSEKEY_MAX_SPEED      6
    #define MOUSEKEY_TIME_TO_MAX    64
#endif

#ifdef OLED_DRIVER_ENABLE
    #define OLED_DISPLAY_128X64
    #define OLED_BRIGHTNESS 120
#endif

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_SPLIT
    #define RGBLED_SPLIT { 8, 8 }
    #undef RGBLED_NUM
    #define RGBLED_NUM 16
    #define RGBLIGHT_SLEEP
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_LIMIT_VAL 150
    #define RGBLIGHT_LAYERS
    #define RGBLIGHT_LAYERS_RETAIN_VAL
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK
