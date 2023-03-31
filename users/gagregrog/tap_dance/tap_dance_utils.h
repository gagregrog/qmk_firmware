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
} td_user_data;

void tap_dance_begin(
  td_action_config actions[],
  uint8_t num_actions,
  tap_dance_state_t *state,
  void *user_data
);

void tap_dance_end(
  td_action_config actions[],
  uint8_t num_actions,
  tap_dance_state_t *state,
  void *user_data
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

#define ACTION_TAP_DANCE_WRAPPER( \
  user_dance_begin, \
  user_dance_end \
) { \
  .fn = { \
    NULL, \
    (void *)user_dance_begin, \
    (void *)user_dance_end \
  }, \
  .user_data = (void *)&((td_user_data) { .pressed = false }), \
}

#define TD_ARGS tap_dance_state_t *state, void *user_data
#define TAP_DANCE_BEGIN(actions) tap_dance_begin(actions, ARRAY_SIZE(actions), state, user_data)
#define TAP_DANCE_END(actions) tap_dance_end(actions, ARRAY_SIZE(actions), state, user_data)
