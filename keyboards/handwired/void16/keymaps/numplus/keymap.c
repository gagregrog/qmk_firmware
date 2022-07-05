/* Copyright 2020 Victor Lucachi
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
#include QMK_KEYBOARD_H

uint32_t last_light_mode;

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN,
    _COLORS,
};

enum custom_keycodes {
    RGB_SPD_INC = SAFE_RANGE,
    RGB_SPD_DEC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base
 * ,--------------------------------.
 * |   7  |   8  |   9  |TOGGLE_LEDS|
 * |------+------+------+-----------|
 * |   4  |   5  |   6  |   BSPACE  |
 * |------+------+------+-----------|
 * |   1  |   2  |   3  |    SPACE  |
 * |------+------+------+-----------|
 * | (FN) |   0  |   .  |   ENTER   |
 * `--------------------------------'
 */

[_BASE] = LAYOUT_ortho_4x4(
    KC_P7,    KC_P8,  KC_P9,    RGB_TOG,
    KC_P4,    KC_P5,  KC_P6,    KC_BSPC,
    KC_P1,    KC_P2,  KC_P3,    KC_SPACE,
    TT(_FN),  KC_P0,  KC_PDOT,  KC_PENT
),

/* FN
 * ,------------------------------.
 * | RESET |        |   /  |  -   |
 * |-------+--------+------+------|
 * |       |   UP   |   *  |   +  |
 * |-------+--------+------+------|
 * |  LEFT |  DOWN  |RIGHT |   =  |
 * |-------+--------+------+------|
 * |(TRANS)|(COLORS)|      |ENTER |
 * `------------------------------'
 */
[_FN] = LAYOUT_ortho_4x4(
    RESET,    KC_NO,       KC_PSLS,    KC_PMNS,
    KC_NO,    KC_UP,       KC_PAST,    KC_PPLS,
    KC_LEFT,  KC_DOWN,     KC_RIGHT,   KC_PEQL,
    KC_TRNS,  TT(_COLORS), KC_NO,      KC_PENT
),

/* COLORS
 * ,-----------------------------------------------------------------.
 * | BRIGHTNESS_DOWN | BRIGHTNEESS_UP |               | TOGGLE_LEDS  |
 * |-----------------+----------------+---------------+--------------|
 * | SATURATION_DOWN | SATURATION_UP  |               |              |
 * |-----------------+----------------+---------------+--------------|
 * |    HUE_DOWN     |     HUE_UP     | SPEED_DOWN    |   SPEED_UP   |
 * |-----------------+----------------+---------------+--------------|
 * |     (BASE)      |                | MODE_BACKWARD | MODE_FORWARD |
 * `-----------------------------------------------------------------'
 */
[_COLORS] = LAYOUT_ortho_4x4(
    RGB_VAD,    RGB_VAI,  KC_NO,        RGB_TOG,
    RGB_SAD,    RGB_SAI,  KC_NO,        KC_NO,
    RGB_HUD,    RGB_HUI,  RGB_SPD_DEC,  RGB_SPD_INC,
    TO(_BASE),  KC_NO,    RGB_RMOD,     RGB_MOD
),
};

void matrix_init_user(void) {
  rgblight_enable();
};

void matrix_scan_user(void) {
}

uint32_t layer_state_set_user(uint32_t state) {
    uint32_t current_light_mode = rgblight_get_mode();

    // if we're switching away from a color mode, store it
    if (current_light_mode != RGBLIGHT_MODE_STATIC_LIGHT) {
        last_light_mode = current_light_mode;
    }

    switch (biton32(state)) {
    case _BASE:
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(HSV_GREEN);
        break;
    case _FN:
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(HSV_PURPLE);
        break;
    case _COLORS:
        rgblight_mode_noeeprom(last_light_mode);
        break;
    default: //  for any other layers, or the default layer
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(HSV_ORANGE);
        break;
    }
  return state;
}

void keyboard_post_init_user(void) {
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv(HSV_GREEN);
    last_light_mode = RGBLIGHT_MODE_RAINBOW_SWIRL;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case RGB_SPD_DEC: {
                // this doesn't seem to be working
                uint8_t rgb_spd = rgblight_get_speed();
                rgblight_set_speed_noeeprom(rgb_spd - 10);
                break;
            }
            case RGB_SPD_INC: {
                // this doesn't seem to be working
                uint8_t rgb_spd = rgblight_get_speed();
                rgblight_set_speed_noeeprom(rgb_spd + 10);
                break;
            }
        }
    }

    return true;
};
