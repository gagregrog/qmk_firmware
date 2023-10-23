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

#include QMK_KEYBOARD_H
// include all common keycodes / macros
#include "gagregrog.h"

#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

#ifdef RGBLIGHT_ENABLE
  const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {25, 12, 5};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_LAYER_COLEMAK_DH_HRM] = LAYOUT_wrapper(
    LAYOUT_COLEMAK_DH_HRM
  ),
  [_LAYER_COLEMAK_DH] = LAYOUT_wrapper(
    LAYOUT_COLEMAK_DH
  ),
  [_LAYER_QWERTY_HRM] = LAYOUT_wrapper(
    LAYOUT_QWERTY_HRM
  ),
  [_LAYER_QWERTY] = LAYOUT_wrapper(
    LAYOUT_QWERTY
  ),
  [_LAYER_NUM] = LAYOUT_wrapper(
    HOME_ROW_MOD_CAGS(
      LAYOUT_NUMERIC
    )
  ),
  [_LAYER_UTIL] = LAYOUT_wrapper(
    LAYOUT_UTILITY
  ),
  [_LAYER_SETTINGS] = LAYOUT_wrapper(
    LAYOUT_SETTINGS
  ),
  [_LAYER_AUTOMOUSE] = LAYOUT_wrapper(
    LAYOUT_AUTOMOUSE
  ),
};

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
  rgblight_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
  rgblight_sethsv(HSV_ORANGE);
#endif
  set_auto_mouse_layer(_LAYER_AUTOMOUSE); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
  set_auto_mouse_enable(true);         // always required before the auto mouse feature will work

  // flash each side so cpi is set for each
  pmw33xx_set_cpi(0, is_keyboard_left() ?  SCROLL_CPI : MOUSE_CPI);
}

report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
  static int8_t scroll_debounce_x = 0;
  static int8_t scroll_debounce_y = 0;

  scroll_debounce_x += left_report.x;
  scroll_debounce_y += left_report.y;

  left_report.x = 0;
  left_report.y = 0;

  if (abs(scroll_debounce_x) > 100) {

    left_report.h = scroll_debounce_x > 0 ? -1 : 1;
    scroll_debounce_x = 0;
  }
  if (abs(scroll_debounce_y) > 100) {

    left_report.v = scroll_debounce_y > 0 ? -1 : 1;
    scroll_debounce_y = 0;
  }

  // disable horizontal scrolling (require shift)
  left_report.h = 0;

  return pointing_device_combine_reports(left_report, right_report);
}

// require 8 mouse movements in a row to trigger an auto mouse layer
#define AUTO_MOUSE_BUFFER_TARGET 0b11111111

uint8_t auto_mouse_buffer = 0;
bool auto_mouse_activation(report_mouse_t mouse_report) {
  bool has_movement = mouse_report.x != 0 || mouse_report.y != 0;
  // shift the LSB to make space for the latest 
  auto_mouse_buffer <<= 1;
  // fill the LSB with 1 or 0 if there was any mouse movement
  auto_mouse_buffer |= (uint8_t)has_movement;  
  // only keep the 8 LSBS
  auto_mouse_buffer &= AUTO_MOUSE_BUFFER_TARGET;
  // only count it as a move if the buffer is filled
  bool is_mouse_move = auto_mouse_buffer == AUTO_MOUSE_BUFFER_TARGET;
     
  return is_mouse_move;
}
