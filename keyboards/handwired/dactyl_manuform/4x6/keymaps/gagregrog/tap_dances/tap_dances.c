#include "gagregrog.h"
#include "tap_dances.h"

tap_dance_action_t tap_dance_actions[] = {
  [T_SSPW]   = ACTION_TAP_DANCE_GAGREGROG(tap_dance_ss),
  [T_DL_HS]  = ACTION_TAP_DANCE_DOUBLE(KC_DLR, KC_HASH),
  [T_SCOPE]  = ACTION_TAP_DANCE_GAGREGROG(tap_dance_scope),
};

// tap dance -- screen shot
td_actions_gagregrog_t td_ss_actions[] = {
  KEY__TD_ACTION_GAGREGROG(SCRN_C),
  KEY__TD_ACTION_GAGREGROG(SCRN_S),
};
void tap_dance_ss(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(td_ss_actions);
}

// tap dance -- bf scope
volatile uint16_t bf_scope_timer = 0;
void start_scope(void) {
  if (!bf_scope_timer) {
    bf_scope_timer = timer_read();
    register_code(KC_DOT);
  }
}
td_actions_gagregrog_t td_scope_actions[] = {
  FN__TD_ACTION_GAGREGROG(start_scope),
  KEY__TD_ACTION_GAGREGROG(KC_DOT),
  FN__TD_ACTION_GAGREGROG(start_scope),
  KEY__TD_ACTION_GAGREGROG(KC_DOT)
};
void tap_dance_scope(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(td_scope_actions);
}
void matrix_scan_tap_dance(void) {
  if (bf_scope_timer && timer_elapsed(bf_scope_timer) > 200) {
    tap_code(KC_G);
    unregister_code(KC_DOT);
    bf_scope_timer = 0;
  }
}
