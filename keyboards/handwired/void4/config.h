/*
Copyright 2022 Robert Reed

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xF055
#define PRODUCT_ID 0x3534
#define DEVICE_VER 0x0001
#define MANUFACTURER Robert Reed
#define PRODUCT VOID4

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 2

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW


/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Tap dance max time */
#define TAPPING_TERM 200

/* Keyboard Matrix Assignments
 *
 * Modify to match your wiring
 *
 *                        1   2
 */
#define MATRIX_ROW_PINS { B5, B4 }
#define MATRIX_COL_PINS { E6, D7 }
#define UNUSED_PINS

#define PS2_CLOCK_PIN   D2
#define PS2_DATA_PIN    D1

#define PS2_INT_INIT()  do {    \
    EICRA |= ((1<<ISC21) |      \
              (0<<ISC20));      \
} while (0)
#define PS2_INT_ON()  do {      \
    EIMSK |= (1<<INT2);         \
} while (0)
#define PS2_INT_OFF() do {      \
    EIMSK &= ~(1<<INT2);        \
} while (0)
#define PS2_INT_VECT   INT2_vect


#define PS2_MOUSE_INVERT_X
#define PS2_MOUSE_INVERT_Y
#define PS2_MOUSE_X_MULTIPLIER 5
#define PS2_MOUSE_Y_MULTIPLIER 5

// #define PS2_MOUSE_DEBUG_HID
// #define PS2_MOUSE_DEBUG_RAW
