#include QMK_KEYBOARD_H
#include "gagregrog.h"
#include "tap_dance_utils.h"

void TD_NOOP(void) {};

uint8_t get_action_index(tap_dance_state_t *state, bool pressed) {
  uint8_t is_pressed = pressed ? 1 : 0;
  uint8_t index = (state->count - 1) * 2 + is_pressed;
  return index;
}

void tap_dance_begin(
  td_action_config actions[],
  uint8_t num_actions,
  tap_dance_state_t *state,
  void *user_data
) {
  td_user_data *td_data = (td_user_data *)user_data;
  td_data->pressed = state->pressed;
  uint8_t action_index = get_action_index(state, td_data->pressed);
  if (action_index >= num_actions) { return; }
  td_action_config action = actions[action_index];

  if (action.key > 0) {
    switch (action.key) {
      #if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
        case KC_SECRET_1 ... KC_SECRET_5: 
          send_secret(action.key);
          break;
      #endif
      default:
        if (td_data->pressed) {
          register_code16(action.key);
        } else {
          tap_code16(action.key);
        }
        break;
    }
  } else if (action.layer < TD_MAX_LAYER) {
    // if a layer action is used on a tap action, it will activate the layer indefinitely
    // if a layer action is used on a hold action, it will activate the layer until the hold is released
    if (td_data->pressed) {
      layer_on(action.layer);
    } else {
      layer_invert(action.layer);
    }
  } else if (action.fn != TD_NOOP) {
    action.fn();
  }
}

void tap_dance_end(
  td_action_config actions[],
  uint8_t num_actions,
  tap_dance_state_t *state,
  void *user_data
) {
  td_user_data *td_data = (td_user_data *)user_data;
  uint8_t action_index = get_action_index(state, td_data->pressed);
  if (action_index >= num_actions) { return; }
  td_action_config action = actions[action_index];
  if (action.key > 0) {
    switch (action.key) {
      #if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
        case KC_SECRET_1 ... KC_SECRET_5: break;
      #endif
      default: {
        if (td_data->pressed) {
          unregister_code16(action.key);
        }
      }
    }
  } else if (action.layer < TD_MAX_LAYER && td_data->pressed) {
    // if the aciton is a hold, deactivate the layer now that the td key is released
    layer_off(action.layer);
  }
}
