#include QMK_KEYBOARD_H
#include "gagregrog.h"
#include "tap_dance_utils.h"

void TD_NOOP(void) {};

uint8_t get_action_index(tap_dance_state_t *state, td_tap_t *tap) {
  uint8_t pressed = tap->pressed ? 1 : 0;
  uint8_t index = (state->count - 1) * 2 + pressed;
  return index;
}

void tap_dance_begin(td_action_config actions[], uint8_t num_actions, td_tap_t *tap, tap_dance_state_t *state) {
  tap->pressed = state->pressed;
  uint8_t index = get_action_index(state, tap);
  if (index >= num_actions) { return; }
  td_action_config action = actions[index];

  if (action.key > 0) {
    switch (action.key) {
      #if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
        case KC_SECRET_1 ... KC_SECRET_5: 
          send_secret(action.key);
          break;
      #endif
      default:
        if (tap->pressed) {
          register_code16(action.key);
        } else {
          tap_code16(action.key);
        }
        break;
    }
  } else if (action.fn != TD_NOOP) {
    action.fn();
  }
}

void tap_dance_end(td_action_config actions[], uint8_t num_actions, td_tap_t *tap, tap_dance_state_t *state) {
  uint8_t index = get_action_index(state, tap);
  if (index >= num_actions) { return; }
  td_action_config action = actions[index];
  if (action.key > 0) {
    switch (action.key) {
      #if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
        case KC_SECRET_1 ... KC_SECRET_5: break;
      #endif
      default: {
        if (tap->pressed) {
          unregister_code16(action.key);
        }
      }
    }
  }
}
