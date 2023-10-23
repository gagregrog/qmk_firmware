#include QMK_KEYBOARD_H
#include "gagregrog.h"

#if defined(CONSOLE_ENABLE) && defined(RGB_MATRIX_ENABLE)
  void debug_rgb_matrix(bool useNextMode);
#endif

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
    #if defined(CONSOLE_ENABLE) && defined(RGB_MATRIX_ENABLE)
      case RGB_MOD:
      case RGB_TOG:
      if (record->event.pressed) {
        debug_rgb_matrix(keycode == RGB_MOD);
      }
      return true;
    #endif
    // replace with better ifdef
    #ifdef LAYOUT_split_3x5_3_h
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
    #endif // LAYOUT_split_3x5_3_h
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
    #ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
      case AM_TOGGLE:
        if(record->event.pressed) {
            auto_mouse_layer_off(); // disable target layer if needed
            set_auto_mouse_enable((AUTO_MOUSE_ENABLED) ^ 1);
            #ifdef CONSOLE_ENABLE
            xprintf("Toggling Auto Mouse: %d\n", AUTO_MOUSE_ENABLED);
            #endif
        }
        return false;
      case AM_KILL:
        if(record->event.pressed) {
            auto_mouse_layer_off();
        }
        return false;
      case KC_BTN1:
      case KC_BTN2:
        if(mod_state & MOD_MASK_SHIFT) {
          // runs on both press and release since otherwise this is treated
          // as a mouse key and reactivates the mouse layer
          auto_mouse_layer_off();
          return false;
        }
        return true;
    #endif // POINTING_DEVICE_AUTO_MOUSE_ENABLE
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
const key_override_t spc_gui_key_override = ko_make_basic(MOD_BIT_RGUI, KC_SPC, LGUI(KC_BSPC));
const key_override_t spc_alt_key_override = ko_make_basic(MOD_MASK_ALT, KC_SPC, LALT(KC_BSPC));
const key_override_t spc_shift_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_BSPC);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&lcbr_key_override,
  &lbrc_key_override,
  &lprn_key_override,
  &spc_gui_key_override,
  &spc_alt_key_override,
  &spc_shift_key_override,
	NULL // Null terminate the array of overrides!
};
#endif

#if defined(TAP_DANCE_ENABLE) && defined(USE_DEFAULT_TD_ACTIONS)
  tap_dance_action_t tap_dance_actions[] = {
    [T_MV_UL]   = ACTION_TAP_DANCE_DOUBLE(MV_UL, MV_UL_REV),
    [T_MV_U]    = ACTION_TAP_DANCE_DOUBLE(MV_U, MV_U_REV),
    [T_MV_UR]   = ACTION_TAP_DANCE_DOUBLE(MV_UR, MV_UR_REV),
    [T_MV_R]    = ACTION_TAP_DANCE_DOUBLE(MV_R, MV_R_REV),
    [T_MV_C]    = ACTION_TAP_DANCE_DOUBLE(MV_C, MV_C_REV),
    [T_MV_L]    = ACTION_TAP_DANCE_DOUBLE(MV_L, MV_L_REV),
    [T_MV_DL]   = ACTION_TAP_DANCE_DOUBLE(MV_DL, MV_DL_REV),
    [T_MV_D]    = ACTION_TAP_DANCE_DOUBLE(MV_D, MV_D_REV),
    [T_MV_DR]   = ACTION_TAP_DANCE_DOUBLE(MV_DR, MV_DR_REV),
  };

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LGUI_T(KC_S):
    case RGUI_T(KC_E):
    case LSFT_T(KC_T):
    case RSFT_T(KC_N):
        return 130;
    default:
        return TAPPING_TERM;
  }
}
#endif // TAP_DANCE_ENABLE

#if defined(CONSOLE_ENABLE) && defined(RGB_MATRIX_ENABLE)
#include "print.h"

void debug_rgb_matrix(bool useNextMode) {
  uint8_t mode = rgb_matrix_get_mode();
  HSV hsv = rgb_matrix_get_hsv();
  char name[40];
  uint8_t normalizedMode = mode;

  if (useNextMode) {
    normalizedMode += 1;
    if (normalizedMode == RGB_MATRIX_EFFECT_MAX) {
      normalizedMode = 1;
    }
  }

  switch (normalizedMode)
  {
#   ifdef ENABLE_RGB_MATRIX_NONE
    case RGB_MATRIX_NONE:
      strcpy(name, "RGB_MATRIX_NONE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_COLOR
    case RGB_MATRIX_SOLID_COLOR:     // Static single hue, no speed support
      strcpy(name, "RGB_MATRIX_SOLID_COLOR");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_ALPHAS_MODS
    case RGB_MATRIX_ALPHAS_MODS:         // Static dual hue, speed is hue for secondary hue
      strcpy(name, "RGB_MATRIX_ALPHAS_MODS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    case RGB_MATRIX_GRADIENT_UP_DOWN:    // Static gradient top to bottom, speed controls how much gradient changes
      strcpy(name, "RGB_MATRIX_GRADIENT_UP_DOWN");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
    case RGB_MATRIX_GRADIENT_LEFT_RIGHT:    // Static gradient left to right, speed controls how much gradient changes
      strcpy(name, "RGB_MATRIX_GRADIENT_LEFT_RIGHT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BREATHING
    case RGB_MATRIX_BREATHING:           // Single hue brightness cycling animation
      strcpy(name, "RGB_MATRIX_BREATHING");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_SAT
    case RGB_MATRIX_BAND_SAT:        // Single hue band fading saturation scrolling left to right
      strcpy(name, "RGB_MATRIX_BAND_SAT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_VAL
    case RGB_MATRIX_BAND_VAL:        // Single hue band fading brightness scrolling left to right
      strcpy(name, "RGB_MATRIX_BAND_VAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
    case RGB_MATRIX_BAND_PINWHEEL_SAT:   // Single hue 3 blade spinning pinwheel fades saturation
      strcpy(name, "RGB_MATRIX_BAND_PINWHEEL_SAT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
    case RGB_MATRIX_BAND_PINWHEEL_VAL:   // Single hue 3 blade spinning pinwheel fades brightness
      strcpy(name, "RGB_MATRIX_BAND_PINWHEEL_VAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
    case RGB_MATRIX_BAND_SPIRAL_SAT:     // Single hue spinning spiral fades saturation
      strcpy(name, "RGB_MATRIX_BAND_SPIRAL_SAT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
    case RGB_MATRIX_BAND_SPIRAL_VAL:     // Single hue spinning spiral fades brightness
      strcpy(name, "RGB_MATRIX_BAND_SPIRAL_VAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_ALL
    case RGB_MATRIX_CYCLE_ALL:           // Full keyboard solid hue cycling through full gradient
      strcpy(name, "RGB_MATRIX_CYCLE_ALL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    case RGB_MATRIX_CYCLE_LEFT_RIGHT:    // Full gradient scrolling left to right
      strcpy(name, "RGB_MATRIX_CYCLE_LEFT_RIGHT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    case RGB_MATRIX_CYCLE_UP_DOWN:       // Full gradient scrolling top to bottom
      strcpy(name, "RGB_MATRIX_CYCLE_UP_DOWN");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    case RGB_MATRIX_CYCLE_OUT_IN:        // Full gradient scrolling out to in
      strcpy(name, "RGB_MATRIX_CYCLE_OUT_IN");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    case RGB_MATRIX_CYCLE_OUT_IN_DUAL:   // Full dual gradients scrolling out to in
      strcpy(name, "RGB_MATRIX_CYCLE_OUT_IN_DUAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    case RGB_MATRIX_RAINBOW_MOVING_CHEVRON:  // Full gradient Chevron shapped scrolling left to right
      strcpy(name, "RGB_MATRIX_RAINBOW_MOVING_CHEVRON");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
    case RGB_MATRIX_CYCLE_PINWHEEL:      // Full gradient spinning pinwheel around center of keyboard
      strcpy(name, "RGB_MATRIX_CYCLE_PINWHEEL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
    case RGB_MATRIX_CYCLE_SPIRAL:        // Full gradient spinning spiral around center of keyboard
      strcpy(name, "RGB_MATRIX_CYCLE_SPIRAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_DUAL_BEACON
    case RGB_MATRIX_DUAL_BEACON:         // Full gradient spinning around center of keyboard
      strcpy(name, "RGB_MATRIX_DUAL_BEACON");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_RAINBOW_BEACON
    case RGB_MATRIX_RAINBOW_BEACON:      // Full tighter gradient spinning around center of keyboard
      strcpy(name, "RGB_MATRIX_RAINBOW_BEACON");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    case RGB_MATRIX_RAINBOW_PINWHEELS:   // Full dual gradients spinning two halfs of keyboard
      strcpy(name, "RGB_MATRIX_RAINBOW_PINWHEELS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_RAINDROPS
    case RGB_MATRIX_RAINDROPS:           // Randomly changes a single key's hue
      strcpy(name, "RGB_MATRIX_RAINDROPS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    case RGB_MATRIX_JELLYBEAN_RAINDROPS: // Randomly changes a single key's hue and saturation
      strcpy(name, "RGB_MATRIX_JELLYBEAN_RAINDROPS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_HUE_BREATHING
    case RGB_MATRIX_HUE_BREATHING:       // Hue shifts up a slight ammount at the same time, then shifts back
      strcpy(name, "RGB_MATRIX_HUE_BREATHING");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_HUE_PENDULUM
    case RGB_MATRIX_HUE_PENDULUM:        // Hue shifts up a slight ammount in a wave to the right, then back to the left
      strcpy(name, "RGB_MATRIX_HUE_PENDULUM");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_HUE_WAVE
    case RGB_MATRIX_HUE_WAVE:            // Hue shifts up a slight ammount and then back down in a wave to the right
      strcpy(name, "RGB_MATRIX_HUE_WAVE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
    case RGB_MATRIX_PIXEL_FRACTAL:       // Single hue fractal filled keys pulsing horizontally out to edges
      strcpy(name, "RGB_MATRIX_PIXEL_FRACTAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_PIXEL_FLOW
    case RGB_MATRIX_PIXEL_FLOW:          // Pulsing RGB flow along LED wiring with random hues
      strcpy(name, "RGB_MATRIX_PIXEL_FLOW");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_PIXEL_RAIN
    case RGB_MATRIX_PIXEL_RAIN:          // Randomly light keys with random hues
      strcpy(name, "RGB_MATRIX_PIXEL_RAIN");
      break;
#   endif
#   if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_TYPING_HEATMAP)
    case RGB_MATRIX_TYPING_HEATMAP:      // How hot is your WPM!
      strcpy(name, "RGB_MATRIX_TYPING_HEATMAP");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_DIGITAL_RAIN
    case RGB_MATRIX_DIGITAL_RAIN:        // That famous computer simulation
      strcpy(name, "RGB_MATRIX_DIGITAL_RAIN");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    case RGB_MATRIX_SOLID_REACTIVE_SIMPLE:   // Pulses keys hit to hue & value then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_SIMPLE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE
    case RGB_MATRIX_SOLID_REACTIVE:      // Static single hue, pulses keys hit to shifted hue then fades to current hue
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    case RGB_MATRIX_SOLID_REACTIVE_WIDE:        // Hue & value pulse near a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_WIDE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    case RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE:   // Hue & value pulse near multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    case RGB_MATRIX_SOLID_REACTIVE_CROSS:       // Hue & value pulse the same column and row of a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_CROSS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    case RGB_MATRIX_SOLID_REACTIVE_MULTICROSS:  // Hue & value pulse the same column and row of multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_MULTICROSS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    case RGB_MATRIX_SOLID_REACTIVE_NEXUS:       // Hue & value pulse away on the same column and row of a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_NEXUS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    case RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS:  // Hue & value pulse away on the same column and row of multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SPLASH
    case RGB_MATRIX_SPLASH:              // Full gradient & value pulse away from a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SPLASH");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_MULTISPLASH
    case RGB_MATRIX_MULTISPLASH:         // Full gradient & value pulse away from multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_MULTISPLASH");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_SPLASH
    case RGB_MATRIX_SOLID_SPLASH:        // Hue & value pulse away from a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_SPLASH");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
    case RGB_MATRIX_SOLID_MULTISPLASH:   // Hue & value pulse away from multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_MULTISPLASH");
      break;
#   endif
    case RGB_MATRIX_EFFECT_MAX:
      strcpy(name, "RGB_MATRIX_EFFECT_MAX");
      break;
    default:
      strcpy(name, "UNKNOWN");
      break;
  }

  uprintf("%i. %s - HSV{%i, %i, %i}\n", mode, name, hsv.h, hsv.s, hsv.v);
}
#endif
