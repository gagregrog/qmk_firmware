/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

/* Key matrix configuration. */
#define MATRIX_ROW_PINS \
    { GP4, GP5, GP27, GP26 }
#define MATRIX_COL_PINS \
    { GP8, GP9, GP7, GP6, GP28 }

/* Handedness. */
#define SPLIT_HAND_PIN GP29
#define SPLIT_HAND_PIN_LOW_IS_LEFT // High -> right, Low -> left.

/* CRC. */
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

/* serial.c configuration (for split keyboard). */
#undef  SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN GP0

#undef  DIODE_DIRECTION
#define DIODE_DIRECTION COL2ROW

/* Cirque trackpad over SPI. */
#define SPI_SCK_PIN GP18
#define SPI_MOSI_PIN GP19
#define SPI_MISO_PIN GP20
#define POINTING_DEVICE_CS_PIN GP1

/* OLED Display over I2C*/
#define OLED_DISPLAY_128X64
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP10
#define I2C1_SCL_PIN GP3

// disable one shot modifiers to save on firmware size
#define NO_ACTION_ONESHOT

#define TAPPING_TOGGLE 2
// Home Row Mod settings
#define TAPPING_TERM 175

// permissive hold - pressing a mod-tap key and pressing/releasing a second key before the mod-tap key is released registers the mod-tap immediately, even if before the tapping term has been reached
#define PERMISSIVE_HOLD

#define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE // enables inertial scroll

#undef  RGBLED_NUM
#define RGBLED_NUM 2

#define WS2812_DI_PIN GP17
#define RGBLIGHT_SLEEP
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_BREATHING
#define RGBLIGHT_DEFAULT_HUE 85

#define SPLIT_LAYER_STATE_ENABLE

