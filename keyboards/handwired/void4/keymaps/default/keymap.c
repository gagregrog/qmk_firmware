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

enum mouse_modes {
  mm_scroll = 0,
  mm_volume,
};

enum my_keycodes {
  MOUSE_MODE_TOGGLE = SAFE_RANGE
};

uint8_t mouse_mode = mm_scroll;
bool mouseModePress = false;
bool mouseModeLock = false;
uint8_t mouseCount = 0;
uint8_t mouseDebounce = 3;

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base

 * ,------+------.
 * |   1  |   2  |
 * |------+------|
 * |   3  |   4  |
 * `-------------'
 * 
 * ,------+------+------+------.
 * |   1  |   2  |   3  |   4  |
 * `------+------+------+------'
 */
[_BASE] = LAYOUT_ortho_2x2(
     KC_BTN1,  KC_BTN2,  KC_BTN3,  MOUSE_MODE_TOGGLE
),

};

void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
  // process special mouse mode whether pressed or locked
  bool mouseModeActive = mouseModePress || mouseModeLock;

  // only handle special mouse modes when enabled by press or lock
  if (!mouseModeActive) {
    return;
  }

  // debounce mouse mode actions so it is more controllable
  if (mouseCount > mouseDebounce) {
    mouseCount = 0;
  }

  // only register mouse mode behavior once every mouseDebounce times
  if (!mouseCount) {
    switch (mouse_mode) {
      case mm_scroll:
        // reassign normal mouse movement to scroll movement
        mouse_report->h = mouse_report->x / -3;
        mouse_report->v = mouse_report->y / 3;
        break;
      case mm_volume:
        // adust volume based on mouse movement
        if (mouse_report->y < 0) {
          tap_code_delay(KC_KB_VOLUME_UP, 10);
        } else if (mouse_report->y > 0) {
          tap_code_delay(KC_KB_VOLUME_DOWN, 10);
        } 
        break;
      default:
        break;
    }
  }
  
  // disable normal mouse movement
  // must happen after the switch statement above
  mouse_report->x = 0;
  mouse_report->y = 0;

  // increment counter to limit scroll processing
  mouseCount++;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MOUSE_MODE_TOGGLE:
      mouseModePress = record->event.pressed;
      return false; // Skip all further processing of this key
    case KC_BTN1:
      if (mouseModePress && record->event.pressed) {
        mouse_mode = mm_scroll;
        return false; // Skip all further processing of this key
      }
      return true; // Process normally when mouseModePress isn't pressed
    case KC_BTN2:
      if (mouseModePress && record->event.pressed) {
        mouse_mode = mm_volume;
        return false; // Skip all further processing of this key
      }
      return true; // Process normally when mouseModePress isn't pressed
    case KC_BTN3:
      if (mouseModePress && record->event.pressed) {
        // toggle the lock
        mouseModeLock = !mouseModeLock;
        return false; // Skip all further processing of this key
      }
      return true; // Process normally when mouseModePress isn't pressed
    default:
      return true; // Process all other key codes normally
  }
}

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
