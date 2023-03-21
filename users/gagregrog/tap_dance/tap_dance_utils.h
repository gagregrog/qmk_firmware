#include "quantum.h"

#pragma once

typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP,
  TD_DOUBLE_HOLD,
  TD_TRIPLE_TAP,
  TD_TRIPLE_HOLD,
} td_state_t;

typedef struct {
  bool is_press_action;
  td_state_t state;
} td_tap_t;

typedef void (td_user_fn_t)(void);

typedef struct {
  uint16_t key;
  td_user_fn_t *fn;
} td_user_config;

typedef struct {
  td_user_config key_single_tap;
  td_user_config key_single_hold;
  td_user_config key_double_tap;
  td_user_config key_double_hold;
  td_user_config key_triple_tap;
  td_user_config key_triple_hold;
} td_custom_config;

void tap_dance_begin(td_custom_config keys, td_tap_t *tap_state, tap_dance_state_t *state);

void tap_dance_end(td_custom_config keys, td_tap_t *tap_state, tap_dance_state_t *state);

td_custom_config ACTION_TAP_DANCE_CUSTOM(
  td_user_config key_single_tap,
  td_user_config key_single_hold,
  td_user_config key_double_tap,
  td_user_config key_double_hold,
  td_user_config key_triple_tap,
  td_user_config key_triple_hold
);

td_user_config ACTION_TAP_DANCE_CONFIG_KEY(uint16_t key);

td_user_config ACTION_TAP_DANCE_CONFIG_FN(td_user_fn_t fn);

td_user_config ACTION_TAP_DANCE_NULL(void);
