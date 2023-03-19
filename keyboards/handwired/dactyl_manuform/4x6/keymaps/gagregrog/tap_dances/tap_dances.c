#include "gagregrog.h"
#include "tap_dances.h"

static td_tap_t sspw_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

static td_tap_t scope_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

#define TD_SSPW_CUSTOM ACTION_TAP_DANCE_CUSTOM( \
  ACTION_TAP_DANCE_CONFIG_KEY(SCRN_C), \
  ACTION_TAP_DANCE_CONFIG_KEY(SCRN_S), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_NO), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_NO), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_NO), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_NO) \
)

void sspw_finished(tap_dance_state_t *state, void *user_data) {
  tap_dance_begin(
    TD_SSPW_CUSTOM,
    &sspw_tap_state,
    state,
    user_data
  );
}

void sspw_reset(tap_dance_state_t *state, void *user_data) {
  tap_dance_end(
    TD_SSPW_CUSTOM,
    &sspw_tap_state,
    state,
    user_data
  );
}

uint16_t bf_scope_timer = 0;

void start_scope(void) {
  if (!bf_scope_timer) {
    bf_scope_timer = timer_read();
    register_code(KC_DOT);
  }
}

#define TD_SCOPE_CUSTOM ACTION_TAP_DANCE_CUSTOM( \
  ACTION_TAP_DANCE_CONFIG_FN(start_scope), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_DOT), \
  ACTION_TAP_DANCE_CONFIG_FN(start_scope), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_DOT), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_NO), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_NO) \
)

void scope_finished(tap_dance_state_t *state, void *user_data) {
  tap_dance_begin(
    TD_SCOPE_CUSTOM,
    &scope_tap_state,
    state,
    user_data
  );
}

void scope_reset(tap_dance_state_t *state, void *user_data) {
  tap_dance_end(
    TD_SCOPE_CUSTOM,
    &scope_tap_state,
    state,
    user_data
  );
}

tap_dance_action_t tap_dance_actions[] = {
  [T_SSPW]   = ACTION_TAP_DANCE_FN_ADVANCED(
    NULL,
    sspw_finished,
    sspw_reset
  ),
  [T_DL_HS]  = ACTION_TAP_DANCE_DOUBLE(
    KC_DLR,
    KC_HASH
  ),
  [T_SCOPE]  = ACTION_TAP_DANCE_FN_ADVANCED(
    NULL,
    scope_finished,
    scope_reset
  ),
};

void matrix_scan_tap_dance(void) {
  if (bf_scope_timer && timer_elapsed(bf_scope_timer) > 200) {
    tap_code(KC_G);
    unregister_code(KC_DOT);
    bf_scope_timer = 0;
  }
}
