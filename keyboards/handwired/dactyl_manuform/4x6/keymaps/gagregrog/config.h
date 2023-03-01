/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#ifdef PS2_DRIVER_USART
#define PS2_CLOCK_PIN   D5
#define PS2_DATA_PIN    D2

/* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
/* set DDR of CLOCK as input to be slave */
#define PS2_USART_INIT() do {   \
    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
    UCSR1C = ((1 << UMSEL10) |  \
              (3 << UPM10)   |  \
              (0 << USBS1)   |  \
              (3 << UCSZ10)  |  \
              (0 << UCPOL1));   \
    UCSR1A = 0;                 \
    UBRR1H = 0;                 \
    UBRR1L = 0;                 \
} while (0)
#define PS2_USART_RX_INT_ON() do {  \
    UCSR1B = ((1 << RXCIE1) |       \
              (1 << RXEN1));        \
} while (0)
#define PS2_USART_RX_POLL_ON() do { \
    UCSR1B = (1 << RXEN1);          \
} while (0)
#define PS2_USART_OFF() do {    \
    UCSR1C = 0;                 \
    UCSR1B &= ~((1 << RXEN1) |  \
                (1 << TXEN1));  \
} while (0)
#define PS2_USART_RX_READY      (UCSR1A & (1<<RXC1))
#define PS2_USART_RX_DATA       UDR1
#define PS2_USART_ERROR         (UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1)))
#define PS2_USART_RX_VECT       USART1_RX_vect

#define PS2_MOUSE_INVERT_X
#define PS2_MOUSE_INVERT_Y
#define PS2_MOUSE_X_MULTIPLIER 5
#define PS2_MOUSE_Y_MULTIPLIER 5
#endif // PS2_DRIVER_USART


/* Select hand configuration */
//#define MASTER_LEFT
//#define MASTER_RIGHT

/* Use I2C or Serial, not both */
#define USE_SERIAL
#undef USE_I2C

/* Select hand configuration */
#define EE_HANDS

#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { B5, B4, E6, D7, C6, D4 }

#undef RGBLED_NUM
#define RGBLED_NUM 14

// Synchronization of the RGB light modes between the two controllers
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT { 7, 7 }

#define RGBLIGHT_LIMIT_VAL 200 /* The maximum brightness level */
#define RGBLIGHT_SLEEP  /* RGB lighting will be switched off when the host goes to sleep */
#define RGBLIGHT_DEFAULT_VAL 175

#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST

// #define AUTO_SHIFT_TIMEOUT 150
// #define AUTO_SHIFT_NO_AUTO_REPEAT

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
