/**
 * Copyright 2023 Gary Gregory Rogers <gagregrog@gmail.com> (@gagregrog)
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

// use the more natural handwire matrix wiring
#define DILEMMA_HANDWIRE_3x5_3

/* serial.c configuration (for split keyboard). */
#undef  SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN GP0

#undef  DIODE_DIRECTION
#define DIODE_DIRECTION COL2ROW

/* Cirque trackpad over SPI. */
#undef  SPI_SCK_PIN
#define SPI_SCK_PIN GP18
#undef  SPI_MOSI_PIN
#define SPI_MOSI_PIN GP19
#undef  SPI_MISO_PIN
#define SPI_MISO_PIN GP20
#undef  POINTING_DEVICE_CS_PIN
#define POINTING_DEVICE_CS_PIN GP1

#undef I2C1_CLOCK_SPEED
#undef I2C1_DUTY_CYCLE
#undef OLED_DISPLAY_HEIGHT

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

// ignore mod tap interrupt - don't trigger the mod tap right when a second key is pressed, instead wait for the tapping term to ensure the mod key is still pressed
#define IGNORE_MOD_TAP_INTERRUPT

// tapping force hold - disable key repeat on quick tap followed by a press for mod-tap keys
#define TAPPING_FORCE_HOLD

// permissive hold - pressing a mod-tap key and pressing/releasing a second key before the mod-tap key is released registers the mod-tap immediately, even if before the tapping term has been reached
#define PERMISSIVE_HOLD

#define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE // enables inertial scroll

#undef  RGBLED_SPLIT
#undef  RGBLED_NUM
#define RGBLED_NUM 2

#undef  RGB_DI_PIN
#define RGB_DI_PIN GP17
#define RGBLIGHT_SLEEP
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_BREATHING
#define RGBLIGHT_DEFAULT_HUE 85

#define SPLIT_LAYER_STATE_ENABLE

#define USE_LAYOUT_3x5_3
#define OLED_FLIP_180
#define OLED_SHOW_DOGS
#define BASIC_BREATH
