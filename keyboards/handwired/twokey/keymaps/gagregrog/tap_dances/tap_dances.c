#include "gagregrog.h"
#include "tap_dances.h"

// - T_ONE
static void hello(void) {
  SEND_STRING("hello");
}

static td_action_config actions_one[] = {
  ACTION_TAP_DANCE_CONFIG_KEY(KC_1),
  ACTION_TAP_DANCE_CONFIG_FN(hello),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_2),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_B),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_3),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_C),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_4),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_D),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_5),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_E),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_6),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_F),
};

static td_tap_t one_state = TD_INIT_STATE;

void one_begin(tap_dance_state_t *state, void *user_data) {
  tap_dance_begin(
    actions_one,
    12,
    &one_state,
    state
  );
}

void one_end(tap_dance_state_t *state, void *user_data) {
  tap_dance_end(
    actions_one,
    12,
    &one_state,
    state
  );
}

// - T_TWO
static void goodbye(void) {
  SEND_STRING("goodbye");
}

static td_action_config actions_two[] = {
  ACTION_TAP_DANCE_CONFIG_FN(goodbye),      // 1
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_KEY(KC_P),        // 2
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_NULL,             // 3
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_NULL,             // 4
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_NULL,             // 5
  ACTION_TAP_DANCE_CONFIG_BOOT
};

static td_tap_t two_state = TD_INIT_STATE;

void two_begin(tap_dance_state_t *state, void *user_data) {
  tap_dance_begin(
    actions_two,
    10,
    &two_state,
    state
  );
}

void two_end(tap_dance_state_t *state, void *user_data) {
  tap_dance_end(
    actions_two,
    6,
    &two_state,
    state
  );
}

tap_dance_action_t tap_dance_actions[] = {
  [T_ONE]  = ACTION_TAP_DANCE_WRAPPER(one_begin, one_end),
  [T_TWO]  = ACTION_TAP_DANCE_WRAPPER(two_begin, two_end),
};
