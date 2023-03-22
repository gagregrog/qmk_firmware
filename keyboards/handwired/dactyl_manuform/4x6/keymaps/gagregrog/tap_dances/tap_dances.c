#include "gagregrog.h"
#include "tap_dances.h"

static td_tap_t sspw_tap_state = TD_INIT_STATE;

td_action_config TD_SSPW_CUSTOM[] = {
  ACTION_TAP_DANCE_CONFIG_KEY(SCRN_C),
  ACTION_TAP_DANCE_CONFIG_KEY(SCRN_S),
};

void sspw_begin(tap_dance_state_t *state, void *user_data) {
  tap_dance_begin(
    TD_SSPW_CUSTOM,
    2,
    &sspw_tap_state,
    state
  );
}

void sspw_end(tap_dance_state_t *state, void *user_data) {
  tap_dance_end(
    TD_SSPW_CUSTOM,
    2,
    &sspw_tap_state,
    state
  );
}

uint16_t bf_scope_timer = 0;

void start_scope(void) {
  if (!bf_scope_timer) {
    bf_scope_timer = timer_read();
    register_code(KC_DOT);
  }
}

static td_tap_t scope_tap_state = TD_INIT_STATE;

td_action_config TD_SCOPE_CUSTOM[] = {
  ACTION_TAP_DANCE_CONFIG_FN(start_scope),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_DOT),
  ACTION_TAP_DANCE_CONFIG_FN(start_scope),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_DOT)
};

void scope_begin(tap_dance_state_t *state, void *user_data) {
  tap_dance_begin(
    TD_SCOPE_CUSTOM,
    4,
    &scope_tap_state,
    state
  );
}

void scope_end(tap_dance_state_t *state, void *user_data) {
  tap_dance_end(
    TD_SCOPE_CUSTOM,
    4,
    &scope_tap_state,
    state
  );
}

tap_dance_action_t tap_dance_actions[] = {
  [T_SSPW]   = ACTION_TAP_DANCE_WRAPPER(
    sspw_begin,
    sspw_end
  ),
  [T_DL_HS]  = ACTION_TAP_DANCE_DOUBLE(
    KC_DLR,
    KC_HASH
  ),
  [T_SCOPE]  = ACTION_TAP_DANCE_WRAPPER(
    scope_begin,
    scope_end
  ),
};

void matrix_scan_tap_dance(void) {
  if (bf_scope_timer && timer_elapsed(bf_scope_timer) > 200) {
    tap_code(KC_G);
    unregister_code(KC_DOT);
    bf_scope_timer = 0;
  }
}
