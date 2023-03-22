#include "gagregrog.h"
#include "tap_dances.h"

// - T_ONE
static td_tap_t one_state = TD_INIT_STATE;
static td_action_config actions_one[] = {
  ACTION_TAP_DANCE_CONFIG_KEY(SCRN_C),
  ACTION_TAP_DANCE_CONFIG_KEY(SCRN_S),
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_KEY(KC_SECRET_1),
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_BOOT
};
void one_begin(tap_dance_state_t *state, void *user_data) {
  tap_dance_begin(
    actions_one,
    10,
    &one_state,
    state
  );
}
void one_end(tap_dance_state_t *state, void *user_data) {
  tap_dance_end(
    actions_one,
    10,
    &one_state,
    state
  );
}

// - T_TWO
static td_tap_t two_state = TD_INIT_STATE;
static td_action_config actions_two[] = {
  ACTION_TAP_DANCE_CONFIG_KEY(KC_SECRET_2),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_SECRET_3)
};
void two_begin(tap_dance_state_t *state, void *user_data) {
  tap_dance_begin(
    actions_two,
    2,
    &two_state,
    state
  );
}

void two_end(tap_dance_state_t *state, void *user_data) {
  tap_dance_end(
    actions_two,
    2,
    &two_state,
    state
  );
}

tap_dance_action_t tap_dance_actions[] = {
  [T_ONE]  = ACTION_TAP_DANCE_WRAPPER(one_begin, one_end),
  [T_TWO]  = ACTION_TAP_DANCE_WRAPPER(two_begin, two_end),
};
