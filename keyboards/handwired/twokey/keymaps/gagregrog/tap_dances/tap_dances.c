#include "gagregrog.h"
#include "tap_dances.h"

// - All Tap Dances

tap_dance_action_t tap_dance_actions[] = {
  [T_ONE]  = ACTION_TAP_DANCE_WRAPPER(one_tap_handle),
  [T_TWO]  = ACTION_TAP_DANCE_WRAPPER(two_tap_handle),
};


// - T_ONE
static td_action_config actions_one[] = {
  ACTION_TAP_DANCE_CONFIG_KEY(SCRN_C),
  ACTION_TAP_DANCE_CONFIG_KEY(SCRN_S),
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_KEY(KC_OS_LOCK),
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_KEY(KC_SECRET_1),
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_NULL,
  ACTION_TAP_DANCE_CONFIG_BOOT,
  ACTION_TAP_DANCE_CONFIG_BOOT
};
void one_tap_handle(TD_ARGS) {
  HANDLE_TAP_DANCE(actions_one);
}


// - T_TWO
void commit_selected(void) {
  tap_code16(LGUI(KC_K));
  wait_ms(50);
  tap_code16(LGUI(LALT(KC_S)));
}
static td_action_config actions_two[] = {
  ACTION_TAP_DANCE_CONFIG_KEY(KC_SECRET_2),
  ACTION_TAP_DANCE_CONFIG_KEY(KC_SECRET_3),
  ACTION_TAP_DANCE_CONFIG_FN(commit_selected),
};
void two_tap_handle(TD_ARGS) {
  HANDLE_TAP_DANCE(actions_two);
}
