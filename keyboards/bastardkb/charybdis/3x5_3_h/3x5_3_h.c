/*
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Publicw License as published by
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

#include QMK_KEYBOARD_H

// clang-format off
#ifdef RGB_MATRIX_ENABLE
/**
 * \brief LEDs index.
 *
 * ╭────────────────────╮                 ╭────────────────────╮
 *    1   6   7  12  13                     31  30  25  24  19
 * ├────────────────────┤                 ├────────────────────┤
 *    2   5   8  11  14                     32  29  26  23  20
 * ├────────────────────┤                 ├────────────────────┤
 *    3   4   9  10  15                     33  28  27  22  21
 * ╰────────────────────╯                 ╰────────────────────╯
 *                   16  17  18     36  35  34
 *                 ╰────────────╯ ╰────────────╯
 *
 * Note: the LED config simulates 36 LEDs instead of the actual 35 to prevent
 * confusion when testing LEDs during assembly when handedness is not set
 * correctly.  Those fake LEDs are bound to the physical top-left corner.
 */
led_config_t g_led_config = { {
    /* Key Matrix to LED index. */
    // Left split.
    {     0,      5,      6,     11,     12 }, // Top row
    {     1,      4,      7,     10,     13 }, // Middle row
    {     2,      3,      8,     9,      14 }, // Bottom row
    {     NO_LED, NO_LED, 15,    16,     17 }, // Thumb cluster
    // Right split.
    {     18,     23,     24,     29,     30 }, // Top row
    {     19,     22,     25,     28,     31 }, // Middle row
    {     20,     21,     26,     27,     32 }, // Bottom row
    {     NO_LED, NO_LED, 33,     34,     35 }, // Thumb cluster
}, {
    /* LED index to physical position. */
    // Left split.
    /* index=0  */ {   0,   0 }, {   0,  21 }, {   0,  42 }, // col 1 (left most)
    /* index=3  */ {  18,  42 }, {  18,  21 }, {  18,   0 }, // col 2
    /* index=6  */ {  36,   0 }, {  36,  21 }, {  36,  42 }, // col 3
    /* index=9  */ {  54,  42 }, {  54,  21 }, {  54,   0 }, // col 4
    /* index=12 */ {  72,   0 }, {  72,  21 }, {  72,  42 }, // col 5
    /* index=15 */ {  63,  64 }, {  81,  64 }, {  99,  64 }, // Thumb cluster
    // Right split.
    /* index=18 */ { 224,   0 }, { 224,  21 }, { 224,  42 }, // col 10 (right most)
    /* index=21 */ { 206,  42 }, { 206,  21 }, { 206,   0 }, // col 9
    /* index=24 */ { 188,   0 }, { 188,  21 }, { 188,  42 },
    /* index=27 */ { 170,  42 }, { 170,  21 }, { 170,   0 },
    /* index=30 */ { 152,   0 }, { 152,  21 }, { 152,  42 },
    /* index=33 */ { 161,  64 }, { 143,  64 }, { 125,  64 },
}, {
    /* LED index to flag. */
    // Left split.
    /* index=0  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 1
    /* index=3  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 2
    /* index=6  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=9  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=12 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=15 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_MODIFIER, // Thumb cluster
    // Right split.
    /* index=18 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 10
    /* index=21 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 9
    /* index=24 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=27 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=30 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=33 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_MODIFIER, // Thumb cluster
} };
#endif
// clang-format on
