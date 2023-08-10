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

#undef DIODE_DIRECTION
#define DIODE_DIRECTION ROW2COL

/* Trackball angle adjustment. */
// #define ROTATIONAL_TRANSFORM_ANGLE -90

/* RGB settings. */
#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_COUNT 36
#    define RGB_MATRIX_SPLIT \
        { 18, 18 }
#endif

#define CHARYBDIS_MINIMUM_DEFAULT_DPI 800

/* serial.c configuration (for split keyboard). */
#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN GP0

#undef POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_COMBINED
#undef POINTING_DEVICE_INVERT_X
#define POINTING_DEVICE_INVERT_Y_RIGHT
#define POINTING_DEVICE_ROTATION_270_RIGHT

/* Key matrix configuration. */
#define MATRIX_ROW_PINS \
    { GP1, GP2, GP3, GP4 }
#define MATRIX_COL_PINS \
    { GP5, GP6, GP7, GP8, GP9 }

/* Handedness. */
#define SPLIT_HAND_PIN GP28
#define SPLIT_HAND_PIN_LOW_IS_LEFT // High -> right, Low -> left.

/* RGB settings. */
#define RGB_DI_PIN GP10
#define RGBLIGHT_LIMIT_VAL 200 /* The maximum brightness level */
#define RGBLIGHT_SLEEP         /* RGB lighting will be switched off when the host goes to sleep */
#define RGBLIGHT_DEFAULT_VAL 175

/* CRC. */
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

/* SPI config for EEPROM and pmw3389 sensor. */
#define SPI_DRIVER SPID0
#undef SPI_SCK_PIN
#define SPI_SCK_PIN GP18
#undef SPI_MOSI_PIN
#define SPI_MOSI_PIN GP19
#undef SPI_MISO_PIN
#define SPI_MISO_PIN GP20
#undef POINTING_DEVICE_CS_PIN
#define POINTING_DEVICE_CS_PIN GP29

/* PMW3389 settings. */
// #define PMW33XX_CS_DIVISOR 64

// disable one shot modifiers to save on firmware size
#define NO_ACTION_ONESHOT

#define TAPPING_TOGGLE 2
// Home Row Mod settings
#define TAPPING_TERM 175

// ignore mod tap interrupt - don't trigger the mod tap right when a second key is pressed, instead wait for the tapping term to ensure the mod key is still pressed
#define IGNORE_MOD_TAP_INTERRUPT

// tapping force hold - disable key repeat on quick tap followed by a press for mod-tap keys
#define TAPPING_FORCE_HOLD

// permissive hold - pressing a mod-tap key and pressing/releasing a second key before the mod-tap key is released registers the mod-tap immediately, even if before the tapping term has been reached
#define PERMISSIVE_HOLD
