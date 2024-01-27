/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#define KB_CHARYBDIS

#undef DIODE_DIRECTION
#define DIODE_DIRECTION ROW2COL

/* RGB settings. */
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#    define MAX_BRIGHTNESS 175
#    define DEFAULT_BRIGHTNESS 125
#    define WS2812_DI_PIN GP29

#    ifdef RGB_MATRIX_ENABLE
#        define RGB_MATRIX_LED_COUNT 36
#        define RGB_MATRIX_SPLIT \
            { 18, 18 }

// disable all features by default, then only enable the specific ones we want
#        undef ENABLE_RGB_MATRIX_SOLID_COLOR            // Static single hue, no speed support
#        undef ENABLE_RGB_MATRIX_ALPHAS_MODS            // Static dual hue, speed is hue for secondary hue
#        undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN       // Static gradient top to bottom, speed controls how much gradient changes
#        undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT    // Static gradient left to right, speed controls how much gradient changes
#        undef ENABLE_RGB_MATRIX_BREATHING              // Single hue brightness cycling animation
#        undef ENABLE_RGB_MATRIX_BAND_SAT               // Single hue band fading saturation scrolling left to right
#        undef ENABLE_RGB_MATRIX_BAND_VAL               // Single hue band fading brightness scrolling left to right
#        undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT      // Single hue 3 blade spinning pinwheel fades saturation
#        undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL      // Single hue 3 blade spinning pinwheel fades brightness
#        undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT        // Single hue spinning spiral fades saturation
#        undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL        // Single hue spinning spiral fades brightness
#        undef ENABLE_RGB_MATRIX_CYCLE_ALL              // Full keyboard solid hue cycling through full gradient
#        undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT       // Full gradient scrolling left to right
#        undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN          // Full gradient scrolling top to bottom
#        undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON // Full gradient Chevron shapped scrolling left to right
#        undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN           // Full gradient scrolling out to in
#        undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL      // Full dual gradients scrolling out to in
#        undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL         // Full gradient spinning pinwheel around center of keyboard
#        undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL           // Full gradient spinning spiral around center of keyboard
#        undef ENABLE_RGB_MATRIX_DUAL_BEACON            // Full gradient spinning around center of keyboard
#        undef ENABLE_RGB_MATRIX_RAINBOW_BEACON         // Full tighter gradient spinning around center of keyboard
#        undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS      // Full dual gradients spinning two halfs of keyboard
#        undef ENABLE_RGB_MATRIX_RAINDROPS              // Randomly changes a single key's hue
#        undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS    // Randomly changes a single key's hue and saturation
#        undef ENABLE_RGB_MATRIX_HUE_BREATHING          // Hue shifts up a slight ammount at the same time, then shifts back
#        undef ENABLE_RGB_MATRIX_HUE_PENDULUM           // Hue shifts up a slight ammount in a wave to the right, then back to the left
#        undef ENABLE_RGB_MATRIX_HUE_WAVE               // Hue shifts up a slight ammount and then back down in a wave to the right
#        undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL          // Single hue fractal filled keys pulsing horizontally out to edges
#        undef ENABLE_RGB_MATRIX_PIXEL_FLOW             // Pulsing RGB flow along LED wiring with random hues
#        undef ENABLE_RGB_MATRIX_PIXEL_RAIN             // Randomly light keys with random hues
// #if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
#        undef ENABLE_RGB_MATRIX_TYPING_HEATMAP // How hot is your WPM!
#        undef ENABLE_RGB_MATRIX_DIGITAL_RAIN   // That famous computer simulation
// #endif // RGB_MATRIX_FRAMEBUFFER_EFFECTS

// #if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE     // Pulses keys hit to hue & value then fades value out
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE            // Static single hue, pulses keys hit to shifted hue then fades to current hue
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       // Hue & value pulse near a single key hit then fades value out
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  // Hue & value pulse near multiple key hits then fades value out
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS      // Hue & value pulse the same column and row of a single key hit then fades value out
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // Hue & value pulse the same column and row of multiple key hits then fades value out
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS      // Hue & value pulse away on the same column and row of a single key hit then fades value out
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // Hue & value pulse away on the same column and row of multiple key hits then fades value out
#        undef ENABLE_RGB_MATRIX_SPLASH                    // Full gradient & value pulse away from a single key hit then fades value out
#        undef ENABLE_RGB_MATRIX_MULTISPLASH               // Full gradient & value pulse away from multiple key hits then fades value out
#        undef ENABLE_RGB_MATRIX_SOLID_SPLASH              // Hue & value pulse away from a single key hit then fades value out
#        undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH         // Hue & value pulse away from multiple key hits then fades value out
// #    endif // RGB_MATRIX_KEYPRESSES || RGB_MATRIX_KEYRELEASES

// enable the specific animations we want
#        define ENABLE_RGB_MATRIX_CYCLE_ALL
#        define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#        define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#        define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#        define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#        define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#        define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#        define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#        define ENABLE_RGB_MATRIX_DUAL_BEACON
#        define ENABLE_RGB_MATRIX_RAINDROPS
#        define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#        define ENABLE_RGB_MATRIX_HUE_BREATHING

#        define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#        define ENABLE_RGB_MATRIX_TYPING_HEATMAP

#        define RGB_MATRIX_KEYPRESSES
#        define RGB_TRIGGER_ON_KEYDOWN
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#        define ENABLE_RGB_MATRIX_MULTISPLASH

#        undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#        define RGB_MATRIX_MAXIMUM_BRIGHTNESS MAX_BRIGHTNESS
#        undef RGB_MATRIX_DEFAULT_VAL
#        define RGB_MATRIX_DEFAULT_VAL DEFAULT_BRIGHTNESS
#    endif // RGB_MATRIX_ENABLE

#    ifdef RGBLIGHT_ENABLE
#        undef RGBLED_NUM
#        define RGBLED_NUM 36
#        define RGBLIGHT_SPLIT
#        define RGBLED_SPLIT \
            { 18, 18 }
#        define RGBLIGHT_LIMIT_VAL MAX_BRIGHTNESS
#        define RGBLIGHT_DEFAULT_VAL DEFAULT_BRIGHTNESS
#        define RGBLIGHT_SLEEP /* RGB lighting will be switched off when the host goes to sleep */

#        define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#        define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL
#    endif // RGBLIGHT_ENABLE
#endif     // RGB_MATRIX_ENABLE || RGBLIGHT_ENABLE

/* serial.c configuration (for split keyboard). */
#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN GP0

/* Key matrix configuration. */
#define MATRIX_ROW_PINS \
    { GP1, GP2, GP3, GP4 }
#define MATRIX_COL_PINS \
    { GP5, GP6, GP7, GP8, GP9 }

/* Handedness. */
#define SPLIT_HAND_PIN GP28
#define SPLIT_HAND_PIN_LOW_IS_LEFT // High -> right, Low -> left.

/* CRC. */
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

/* SPI config for pmw3389 sensor. */
#define SPI_DRIVER SPID0
#undef SPI_SCK_PIN
#define SPI_SCK_PIN GP18
#undef SPI_MOSI_PIN
#define SPI_MOSI_PIN GP19
#undef SPI_MISO_PIN
#define SPI_MISO_PIN GP20
#undef POINTING_DEVICE_CS_PIN
#define POINTING_DEVICE_CS_PIN GP10

/* PMW3389 settings. */
#define PMW33XX_CS_DIVISOR 64

/* Pointing Device */
#define CHARYBDIS_MINIMUM_DEFAULT_DPI 800
#undef POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_COMBINED
#undef POINTING_DEVICE_INVERT_X
#define POINTING_DEVICE_INVERT_Y_RIGHT
#define POINTING_DEVICE_INVERT_Y
#define POINTING_DEVICE_ROTATION_270_RIGHT
#define POINTING_DEVICE_ROTATION_270

// disable one shot modifiers to save on firmware size
#define NO_ACTION_ONESHOT

#define TAPPING_TOGGLE 2
// Home Row Mod settings
#define TAPPING_TERM 175

// permissive hold - pressing a mod-tap key and pressing/releasing a second key before the mod-tap key is released registers the mod-tap immediately, even if before the tapping term has been reached
#define PERMISSIVE_HOLD
