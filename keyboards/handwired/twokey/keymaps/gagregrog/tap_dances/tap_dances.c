#include "gagregrog.h"
#include "tap_dances.h"

// - All Tap Dances

tap_dance_action_t tap_dance_actions[] = {
  [T_ONE]  = ACTION_TAP_DANCE_GAGREGROG(one_tap_handle),
  [T_TWO]  = ACTION_TAP_DANCE_GAGREGROG(two_tap_handle),
};


// - T_ONE
static td_actions_gagregrog_t actions_one[] = {
  KEY__TD_ACTION_GAGREGROG(SCRN_C),
  KEY__TD_ACTION_GAGREGROG(SCRN_S),
  NULL__TD_ACTION_GAGREGROG,
  KEY__TD_ACTION_GAGREGROG(KC_OS_LOCK),
  NULL__TD_ACTION_GAGREGROG,
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_1),
  NULL__TD_ACTION_GAGREGROG,
  NULL__TD_ACTION_GAGREGROG,
  BOOT__TD_ACTION_GAGREGROG,
  BOOT__TD_ACTION_GAGREGROG
};
void one_tap_handle(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_one);
}


// - T_TWO
void commit_selected(void) {
  tap_code16(LGUI(KC_K));
  wait_ms(50);
  tap_code16(LGUI(LALT(KC_S)));
}
static td_actions_gagregrog_t actions_two[] = {
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_2),
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_3),
  FN__TD_ACTION_GAGREGROG(commit_selected),
};
void two_tap_handle(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_two);
}
