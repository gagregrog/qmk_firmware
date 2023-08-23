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
    left_report.h = -left_report.x;
    left_report.v = -left_report.y;
    left_report.x = 0;
    left_report.y = 0;

    return pointing_device_combine_reports(left_report, right_report);
}
