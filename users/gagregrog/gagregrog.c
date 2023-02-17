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

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true; // Process all other keycodes normally
}

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Store the current modifier state in the variable for later reference
  mod_state = get_mods();

  switch (keycode) {
#ifdef USE_LAYOUT_3x5_3
    case TG_BASE:
      if (record->event.pressed) {
        if (layer_state_is(LAYER_BASE_QWERTY)) {
          layer_off(LAYER_BASE_QWERTY);
        } else {
          layer_on(LAYER_BASE_QWERTY);
        }
      }
      return false;
#endif // USE_LAYOUT_3x5_3
    default:
      return process_record_keymap(keycode, record); 
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
