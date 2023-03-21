#include "gagregrog.h"
#include "tap_dances.h"

// --------------------------------- TD_ONE

static td_tap_t td_one_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

#define TD_ONE_CUSTOM ACTION_TAP_DANCE_CUSTOM( \
  ACTION_TAP_DANCE_CONFIG_KEY(SCRN_C), \
  ACTION_TAP_DANCE_CONFIG_KEY(SCRN_O), \
  ACTION_TAP_DANCE_NULL(), \
  ACTION_TAP_DANCE_NULL(), \
  ACTION_TAP_DANCE_NULL(), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_SECRET_1) \
)

void one_finished(tap_dance_state_t *state, void *user_data) {
  tap_dance_begin(
    TD_ONE_CUSTOM, 
    &td_one_tap_state,
    state
  );
}

void one_reset(tap_dance_state_t *state, void *user_data) {
  tap_dance_end(
    TD_ONE_CUSTOM,
    &td_one_tap_state,
    state
  );
}

// --------------------------------- TD_TWO
static td_tap_t td_two_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void sendHello(void) {
  SEND_STRING("hello");
};

void sendGoodbye(void) {
  SEND_STRING("goodbye");
};

#define TD_TWO_CUSTOM ACTION_TAP_DANCE_CUSTOM( \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_SECRET_2), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_SECRET_3), \
  ACTION_TAP_DANCE_NULL(), \
  ACTION_TAP_DANCE_NULL(), \
  ACTION_TAP_DANCE_NULL(), \
  ACTION_TAP_DANCE_NULL() \
)

void two_finished(tap_dance_state_t *state, void *user_data) {
  tap_dance_begin(
    TD_TWO_CUSTOM,
    &td_two_tap_state,
    state
  );
}

void two_reset(tap_dance_state_t *state, void *user_data) {
  tap_dance_end(
    TD_TWO_CUSTOM,
    &td_two_tap_state,
    state
  );
}

// --------------------------------- TDS

// tap_dance_action_t tap_dance_actions[] = {
//   [T_ONE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, one_finished, one_reset),
//   [T_TWO]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, two_finished, two_reset),
// };

tap_dance_action_t tap_dance_actions[] = {
  [T_ONE]  = ACTION_TAP_DANCE_WRAPPER(one_finished, one_reset),
  [T_TWO]  = ACTION_TAP_DANCE_WRAPPER(two_finished, two_reset),
};
