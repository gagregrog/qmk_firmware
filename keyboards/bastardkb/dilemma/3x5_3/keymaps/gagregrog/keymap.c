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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_LAYER_COLEMAK_DH] = LAYOUT_wrapper(
    HOME_ROW_MOD_CAGS(
      LAYOUT_COLEMAK_DH
    )
  ),
  [_LAYER_QWERTY] = LAYOUT_wrapper(
    HOME_ROW_MOD_CAGS(
      LAYOUT_QWERTY
    )
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
};
