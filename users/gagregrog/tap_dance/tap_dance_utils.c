#include QMK_KEYBOARD_H
#include "gagregrog.h"
#include "tap_dance_utils.h"

void TD_NOOP(void) {};

td_user_config ACTION_TAP_DANCE_CONFIG_KEY(uint16_t key)
{
  return (td_user_config) { .key = key, .fn = TD_NOOP, };
}

td_user_config ACTION_TAP_DANCE_CONFIG_FN(td_user_fn_t fn)
{
  return (td_user_config) { .key = 0, .fn = fn, };
}

td_custom_config ACTION_TAP_DANCE_CUSTOM(
  td_user_config key_single_tap,
  td_user_config key_single_hold,
  td_user_config key_double_tap,
  td_user_config key_double_hold,
  td_user_config key_triple_tap,
  td_user_config key_triple_hold
) {
  return (td_custom_config) {
    .key_single_tap = key_single_tap,
    .key_single_hold = key_single_hold,
    .key_double_tap = key_double_tap,
    .key_double_hold = key_double_hold,
    .key_triple_tap = key_triple_tap,
    .key_triple_hold = key_triple_hold,
  };
}

td_state_t decode_tap_dance_state(tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) return TD_SINGLE_TAP;
    return TD_SINGLE_HOLD;
  }
  
  if (state->count == 2) {
    if (!state->pressed) return TD_DOUBLE_TAP;
    return TD_DOUBLE_HOLD;
  }
  
  if (state->count == 3) {
    if (!state->pressed) return TD_TRIPLE_TAP;
    return TD_TRIPLE_HOLD;
  }
  
  return TD_UNKNOWN;
}

void handle_tap_dance_begin(td_user_config key_config) {
  if (key_config.key > 0) {
    switch (key_config.key) {
      #if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
        case KC_SECRET_1 ... KC_SECRET_5: 
          send_secret(key_config.key);
          break;
      #endif
      default:
        register_code16(key_config.key);
    }
  } else {
    key_config.fn();
  }
}

void handle_tap_dance_end(td_user_config key_config) {
  if (key_config.key > 0) {
    switch (key_config.key) {
      case KC_SECRET_1 ... KC_SECRET_5: break;
      default: unregister_code16(key_config.key);
    }
  }
}

void tap_dance_begin(td_custom_config keys, td_tap_t *tap_state, tap_dance_state_t *state, void *user_data) {
  tap_state->state = decode_tap_dance_state(state);
  switch (tap_state->state) {
    case TD_SINGLE_TAP: handle_tap_dance_begin(keys.key_single_tap); break;
    case TD_SINGLE_HOLD: handle_tap_dance_begin(keys.key_single_hold); break;
    case TD_DOUBLE_TAP: handle_tap_dance_begin(keys.key_double_tap); break;
    case TD_DOUBLE_HOLD: handle_tap_dance_begin(keys.key_double_hold); break;
    case TD_TRIPLE_TAP: handle_tap_dance_begin(keys.key_triple_tap); break;
    case TD_TRIPLE_HOLD: handle_tap_dance_begin(keys.key_triple_hold); break;
    default: break;
  }
}
void tap_dance_end(td_custom_config keys, td_tap_t *tap_state, tap_dance_state_t *state, void *user_data) {
  switch (tap_state->state) {
    case TD_SINGLE_TAP: handle_tap_dance_end(keys.key_single_tap); break;
    case TD_SINGLE_HOLD: handle_tap_dance_end(keys.key_single_hold); break;
    case TD_DOUBLE_TAP: handle_tap_dance_end(keys.key_double_tap); break;
    case TD_DOUBLE_HOLD: handle_tap_dance_end(keys.key_double_hold); break;
    case TD_TRIPLE_TAP: handle_tap_dance_end(keys.key_triple_tap); break;
    case TD_TRIPLE_HOLD: handle_tap_dance_end(keys.key_triple_hold); break;
    default: break;
  }
  tap_state->state = TD_NONE;
}
