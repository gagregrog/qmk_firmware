/*
 * Copyright 2025 Gary Gregory Rogers <gagregrog@gmail.com>
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

/* Pointing device configuration. */

// Enables support for extended i16 mouse reports (instead of i8).
#define MOUSE_EXTENDED_REPORT

// Limits the frequency that the sensor is polled for motion.
#define POINTING_DEVICE_TASK_THROTTLE_MS 10

// Adjust trackpad rotation.
#define POINTING_DEVICE_ROTATION_90

// Configure for the Cirque model used on the Dilemma.
#define CIRQUE_PINNACLE_DIAMETER_MM 35
#define CIRQUE_PINNACLE_CURVED_OVERLAY
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE // Circular scroll.

/* Direct pins for 3 buttons */
#define DIRECT_PINS { \
    { GP26, GP27, GP28 } \
}
#define DIRECT_PINS_INPUT_MODE INPUT_PULLUP

#undef POINTING_DEVICE_ENABLE
#define POINTING_DEVICE_ENABLE

/* Optional Cirque settings */
#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE

#define DEBUG_POINTING_DEVICE
