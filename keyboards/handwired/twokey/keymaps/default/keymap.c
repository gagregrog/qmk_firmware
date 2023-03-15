#include QMK_KEYBOARD_H

// Tap Dance ----------------------------
typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP,
  TD_DOUBLE_HOLD,
  TD_DOUBLE_SINGLE_TAP, // Send two single taps
  TD_TRIPLE_TAP,
  TD_TRIPLE_HOLD,
} td_state_t;

enum {
  T_ONE,
  T_TWO,
};

#define TD_ONE     TD(T_ONE)
#define TD_TWO     TD(T_TWO)

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
} td_quad_config;

void TD_NOOP(void) {};

static inline td_user_config ACTION_TAP_DANCE_CONFIG_KEY(uint16_t key)
{
  return (td_user_config) { .key = key, .fn = TD_NOOP, };
}

static inline td_user_config ACTION_TAP_DANCE_CONFIG_FN(td_user_fn_t fn)
{
  return (td_user_config) { .key = 0, .fn = fn, };
}

static inline td_quad_config ACTION_TAP_DANCE_QUAD(td_user_config key_single_tap, td_user_config key_single_hold, td_user_config key_double_tap, td_user_config key_double_hold)
{
  return (td_quad_config) { .key_single_tap = key_single_tap, .key_single_hold = key_single_hold, .key_double_tap = key_double_tap, .key_double_hold = key_double_hold, };
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_1x2(TD_ONE, TD_TWO)
};

td_state_t cur_dance(tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
    // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
    else return TD_SINGLE_HOLD;
  }
  
  if (state->count == 2) {
    // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
    // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
    // keystrokes of the key, and not the 'double tap' action/macro.
    if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
    else if (state->pressed) return TD_DOUBLE_HOLD;
    else return TD_DOUBLE_TAP;
  }

  // Assumes no one is trying to type the same letter three times (at least not quickly).
  // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
    else return TD_TRIPLE_HOLD;
  }
  
  return TD_UNKNOWN;
}

td_state_t cur_dance_with_hold(tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) return TD_SINGLE_TAP;
    return TD_SINGLE_HOLD;
  }
  
  if (state->count == 2) {
    if (!state->pressed) return TD_DOUBLE_TAP;
    return TD_DOUBLE_HOLD;
  }
  
  return TD_UNKNOWN;
}

static td_tap_t one_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

static td_tap_t two_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void handle_key_down(td_user_config key_config) {
  if (key_config.key > 0) {
    register_code16(key_config.key);
  } else {
    key_config.fn();
  }
}

void handle_key_up(td_user_config key_config) {
  if (key_config.key > 0) {
    unregister_code16(key_config.key);
  }
}

void finished_quad(td_quad_config keys, td_tap_t *tap_state, tap_dance_state_t *state, void *user_data) {
  tap_state->state = cur_dance_with_hold(state);
  switch (tap_state->state) {
    case TD_SINGLE_TAP: handle_key_down(keys.key_single_tap); break;
    case TD_SINGLE_HOLD: handle_key_down(keys.key_single_hold); break;
    case TD_DOUBLE_TAP: handle_key_down(keys.key_double_tap); break;
    case TD_DOUBLE_HOLD: handle_key_down(keys.key_double_hold); break;
    default: break;
  }
}
void reset_quad(td_quad_config keys, td_tap_t *tap_state, tap_dance_state_t *state, void *user_data) {
  switch (tap_state->state) {
    case TD_SINGLE_TAP: handle_key_up(keys.key_single_tap); break;
    case TD_SINGLE_HOLD: handle_key_up(keys.key_single_hold); break;
    case TD_DOUBLE_TAP: handle_key_up(keys.key_double_tap); break;
    case TD_DOUBLE_HOLD: handle_key_up(keys.key_double_hold); break;
    default: break;
  }
  tap_state->state = TD_NONE;
}

void sendPw(void) {
  SEND_STRING("password1");
};

void surprise(void) {
  SEND_STRING("Happy Birthday, Jeroen!");
};

#define SCRN_C    LCTL(SGUI(KC_4))

// left key
// tap once     - copy
// hold         - cut
// tap twice    - undo
// tap and hold - take screenshot
void one_finished(tap_dance_state_t *state, void *user_data) {
  finished_quad(ACTION_TAP_DANCE_QUAD(ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_C)), ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_X)), ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_Z)), ACTION_TAP_DANCE_CONFIG_KEY(SCRN_C)), &one_tap_state, state, user_data);
}
void one_reset(tap_dance_state_t *state, void *user_data) {
  reset_quad(ACTION_TAP_DANCE_QUAD(ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_C)), ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_X)), ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_Z)), ACTION_TAP_DANCE_CONFIG_KEY(SCRN_C)), &one_tap_state, state, user_data);
}

// right key
// tap once     - paste
// hold         - send pw
// tap twice    - redo
// tap and hold - surprise
void two_finished(tap_dance_state_t *state, void *user_data) {
  finished_quad(ACTION_TAP_DANCE_QUAD(ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_V)), ACTION_TAP_DANCE_CONFIG_FN(sendPw), ACTION_TAP_DANCE_CONFIG_KEY(SGUI(KC_Z)), ACTION_TAP_DANCE_CONFIG_FN(surprise)), &two_tap_state, state, user_data);
}
void two_reset(tap_dance_state_t *state, void *user_data) {
  reset_quad(ACTION_TAP_DANCE_QUAD(ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_V)), ACTION_TAP_DANCE_CONFIG_FN(sendPw), ACTION_TAP_DANCE_CONFIG_KEY(SGUI(KC_Z)), ACTION_TAP_DANCE_CONFIG_FN(surprise)), &two_tap_state, state, user_data);
}

tap_dance_action_t tap_dance_actions[] = {
  [T_ONE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, one_finished, one_reset),
  [T_TWO]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, two_finished, two_reset),
};
