#include "quantum.h"

#pragma once

typedef void (td_user_fn_t)(void);

typedef struct {
  uint16_t key;
  td_user_fn_t *fn;
  uint8_t layer;
} td_action_config;

typedef struct {
  bool pressed;
} td_tap_t;

void tap_dance_begin(
  td_action_config actions[],
  uint8_t num_actions,
  td_tap_t *tap,
  tap_dance_state_t *state
);

void tap_dance_end(
  td_action_config actions[],
  uint8_t num_actions,
  td_tap_t *tap,
  tap_dance_state_t *state
);

void TD_NOOP(void);

#define TD_MAX_LAYER 255

#define ACTION_TAP_DANCE_CONFIG_KEY(KEY) { \
  .key = KEY, \
  .fn = TD_NOOP, \
  .layer = TD_MAX_LAYER, \
}
#define ACTION_TAP_DANCE_CONFIG_FN(FN) { \
  .key = 0, \
  .fn = FN, \
  .layer = TD_MAX_LAYER, \
}
#define ACTION_TAP_DANCE_CONFIG_LAYER(LAYER) { \
  .key = 0, \
  .fn = TD_NOOP, \
  .layer = LAYER, \
}
#define ACTION_TAP_DANCE_CONFIG_NULL { \
 .key = 0, \
 .fn = TD_NOOP, \
 .layer = TD_MAX_LAYER, \
}
#define ACTION_TAP_DANCE_CONFIG_BOOT ACTION_TAP_DANCE_CONFIG_FN(reset_keyboard)
#define TD_INIT_STATE { .pressed = false }

#define ACTION_TAP_DANCE_WRAPPER( \
  user_fn_on_dance_begin, \
  user_fn_on_dance_end \
) \
  ACTION_TAP_DANCE_FN_ADVANCED( \
    NULL, \
    user_fn_on_dance_begin, \
    user_fn_on_dance_end \
  )
