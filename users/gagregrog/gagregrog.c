#include "gagregrog.h"

#ifdef POINTING_DEVICE_ENABLE
__attribute__ ((weak))
report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
  return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
#ifdef POINTING_DEVICE_INVERT_SCROLL
  mouse_report.h *= -1;
  mouse_report.v *= -1;
#endif

  return pointing_device_task_keymap(mouse_report);
}
#endif // POINTING_DEVICE_ENABLE

#ifdef TRACKPOINT_ENABLE
  bool msScrollPress = false;
  bool msScrollLock = false;
  bool msEnabled = true;
  uint8_t mouseReportCount = 0;
  uint8_t mouseDebounce = 3;
  bool hasIgnoredFirstReport = false;

  void rotate_mouse_report(report_mouse_t *mouse_report) {
    // https://doubleroot.in/lessons/coordinate-geometry-basics/rotation-of-axes/
    // theta = -pi/4
    const double cos_theta = 0.7071067811865475;
    const double sin_theta = -0.7071067811865475;
    double x_cos = cos_theta * mouse_report->x;
    double y_cos = cos_theta * mouse_report->y;
    double x_sin = sin_theta * mouse_report->x;
    double y_sin = sin_theta * mouse_report->y;
    double x = x_cos - y_sin;
    double y = x_sin + y_cos;
    mouse_report->x = (mouse_xy_report_t) x;
    mouse_report->y = (mouse_xy_report_t) y;
  }

  void ignoreMouseReport(report_mouse_t *mouse_report) {
    mouse_report->x = 0;
    mouse_report->y = 0;
    mouse_report->h = 0;
    mouse_report->v = 0;
    mouse_report->buttons = 0;
  }

  void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
    if (!hasIgnoredFirstReport) {
      // first report always does a right click and jumps the cursor,
      // so let's ignore it
      hasIgnoredFirstReport = true;
      ignoreMouseReport(mouse_report);
      return;
    }

    if (!msEnabled) {
      ignoreMouseReport(mouse_report);
      return;
    }

    // process special mouse mode whether pressed or locked
    bool lockActive = msScrollLock && !msScrollPress;
    bool pressActive = !msScrollLock && msScrollPress;
    bool mouseScrollActive = (lockActive || pressActive);

    // only handle special mouse modes when enabled by press or lock
    if (!mouseScrollActive) {
      return;
    }

    // debounce mouse mode actions so it is more controllable
    if (mouseReportCount > mouseDebounce) {
      mouseReportCount = 0;
    }

    // only register mouse mode behavior once every mouseDebounce times
    if (!mouseReportCount) {
      // reassign normal mouse movement to scroll movement
      mouse_report->h = mouse_report->x / -3;
      mouse_report->v = mouse_report->y / -3;
    }
    
    // disable normal mouse movement
    // must happen after reassigning the movement above
    mouse_report->x = 0;
    mouse_report->y = 0;

    // increment counter to limit scroll processing
    mouseReportCount++;
  }
#endif // TRACKPOINT_ENABLE

#if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}

#endif // INCLUDE_SECRETS


__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true; // Process all other keycodes normally
}

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;
bool hrm_state = true;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef MOUSE_TURBO_CLICK
    if (!process_mouse_turbo_click(keycode, record, MS_TURBO)) { return false; }
  #endif // MOUSE_TURBO_CLICK

  // Store the current modifier state in the variable for later reference
  mod_state = get_mods();

  switch (keycode) {
    // replace with better ifdef
    #ifdef USE_LAYOUT_3x5_3
      case TG_BASE:
        if (record->event.pressed) {
          if (IS_LAYER_ON(_LAYER_QWERTY_HRM)) {
            layer_off(_LAYER_QWERTY_HRM);
          } else if (IS_LAYER_ON(_LAYER_QWERTY)) {
            layer_on(_LAYER_COLEMAK_DH);
            layer_off(_LAYER_QWERTY);
          } else if (IS_LAYER_ON(_LAYER_COLEMAK_DH)) {
            layer_on(_LAYER_QWERTY);
            layer_off(_LAYER_COLEMAK_DH);
          } else {
            layer_on(_LAYER_QWERTY_HRM);
          }
        }
        return false;
      case TG_HRM:
        if (record->event.pressed) {
          if (IS_LAYER_ON(_LAYER_QWERTY_HRM)) {
            layer_on(_LAYER_QWERTY);
            layer_off(_LAYER_QWERTY_HRM);
          } else if (IS_LAYER_ON(_LAYER_QWERTY)) {
            layer_on(_LAYER_QWERTY_HRM);
            layer_off(_LAYER_QWERTY);
          } else if (IS_LAYER_ON(_LAYER_COLEMAK_DH)) {
            layer_off(_LAYER_COLEMAK_DH);
          } else {
            layer_on(_LAYER_COLEMAK_DH);
          }

          hrm_state = !hrm_state;
        }
        return false;
    #endif // USE_LAYOUT_3x5_3
    #ifdef TRACKPOINT_ENABLE
      case MOUSE_SCROLL_PRESS:
        msScrollPress = record->event.pressed;
        return false; // Skip all further processing of this key
      case MOUSE_SCROLL_LOCK:
        if (record->event.pressed) {
          msScrollLock = !msScrollLock;
        }
        return false;
      case MOUSE_TOGGLE:
        if (record->event.pressed) {
          msEnabled = !msEnabled;
        }
        return false;
    #endif // TRACKPOINT_ENABLE
    default:
    #if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
      return process_record_keymap(keycode, record) && process_record_secrets(keycode, record);
    #else
      return process_record_keymap(keycode, record);
    #endif
  }
}

#if defined(KEY_OVERRIDE_ENABLE) && defined(USE_BRACKET_OVERRIDE)
const key_override_t lcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LCBR, KC_RCBR);
const key_override_t lbrc_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_RBRC);
const key_override_t lprn_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_RPRN);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&lcbr_key_override,
  &lbrc_key_override,
  &lprn_key_override,
	NULL // Null terminate the array of overrides!
};
#endif
