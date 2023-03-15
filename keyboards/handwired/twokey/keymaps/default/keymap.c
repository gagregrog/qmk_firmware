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

enum tap_dance_keys {
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
  td_user_config key_triple_tap;
  td_user_config key_triple_hold;
} td_custom_config;

void TD_NOOP(void) {};

static inline td_user_config ACTION_TAP_DANCE_CONFIG_KEY(uint16_t key)
{
  return (td_user_config) { .key = key, .fn = TD_NOOP, };
}

static inline td_user_config ACTION_TAP_DANCE_CONFIG_FN(td_user_fn_t fn)
{
  return (td_user_config) { .key = 0, .fn = fn, };
}

static inline td_custom_config ACTION_TAP_DANCE_CUSTOM(td_user_config key_single_tap, td_user_config key_single_hold, td_user_config key_double_tap, td_user_config key_double_hold, td_user_config key_triple_tap, td_user_config key_triple_hold)
{
  return (td_custom_config) { .key_single_tap = key_single_tap, .key_single_hold = key_single_hold, .key_double_tap = key_double_tap, .key_double_hold = key_double_hold, key_triple_tap = key_triple_tap, .key_triple_hold = key_triple_hold, };
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_1x2(TD_ONE, TD_TWO)
};

td_state_t cur_dance_with_hold(tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) return TD_SINGLE_TAP;
    return TD_SINGLE_HOLD;
  }
  
  if (state->count == 2) {
    if (!state->pressed) return TD_DOUBLE_TAP;
    return TD_DOUBLE_HOLD;
  }
  
  if (state->count == 3) {
    if (!state->pressed) return TD_TRIPLE_TAP;
    return TD_TRIPLE_HOLD;
  }
  
  return TD_UNKNOWN;
}

static td_tap_t td_one_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

static td_tap_t td_two_tap_state = {
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

void td_finished_custom(td_custom_config keys, td_tap_t *tap_state, tap_dance_state_t *state, void *user_data) {
  tap_state->state = cur_dance_with_hold(state);
  switch (tap_state->state) {
    case TD_SINGLE_TAP: handle_key_down(keys.key_single_tap); break;
    case TD_SINGLE_HOLD: handle_key_down(keys.key_single_hold); break;
    case TD_DOUBLE_TAP: handle_key_down(keys.key_double_tap); break;
    case TD_DOUBLE_HOLD: handle_key_down(keys.key_double_hold); break;
    case TD_TRIPLE_TAP: handle_key_down(keys.key_triple_tap); break;
    case TD_TRIPLE_HOLD: handle_key_down(keys.key_triple_hold); break;
    default: break;
  }
}
void td_reset_custom(td_custom_config keys, td_tap_t *tap_state, tap_dance_state_t *state, void *user_data) {
  switch (tap_state->state) {
    case TD_SINGLE_TAP: handle_key_up(keys.key_single_tap); break;
    case TD_SINGLE_HOLD: handle_key_up(keys.key_single_hold); break;
    case TD_DOUBLE_TAP: handle_key_up(keys.key_double_tap); break;
    case TD_DOUBLE_HOLD: handle_key_up(keys.key_double_hold); break;
    case TD_TRIPLE_TAP: handle_key_up(keys.key_triple_tap); break;
    case TD_TRIPLE_HOLD: handle_key_up(keys.key_triple_hold); break;
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

// screenshot to clipboard
#define SCRN_C    LCTL(SGUI(KC_4))

// left key
// tap once            - copy
// hold                - cut
// tap twice           - undo
// tap and hold        - take screenshot
// triple tap          - 
// double tap and hold -
void one_finished(tap_dance_state_t *state, void *user_data) {
    td_finished_custom(
        ACTION_TAP_DANCE_CUSTOM(
            ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_C)),
            ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_X)),
            ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_Z)),
            ACTION_TAP_DANCE_CONFIG_KEY(SCRN_C),
            ACTION_TAP_DANCE_CONFIG_KEY(KC_NO),
            ACTION_TAP_DANCE_CONFIG_KEY(KC_NO)
        ), 
        &td_one_tap_state,
        state,
        user_data
    );
}
void one_reset(tap_dance_state_t *state, void *user_data) {
    td_reset_custom(
        ACTION_TAP_DANCE_CUSTOM(
            ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_C)),
            ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_X)),
            ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_Z)),
            ACTION_TAP_DANCE_CONFIG_KEY(SCRN_C),
            ACTION_TAP_DANCE_CONFIG_KEY(KC_NO),
            ACTION_TAP_DANCE_CONFIG_KEY(KC_NO)
        ),
        &td_one_tap_state,
        state,
        user_data
    );
}

// right key
// tap once            - paste
// hold                - send pw
// tap twice           - redo
// tap and hold        - surprise
// triple tap          - 
// double tap and hold -
void two_finished(tap_dance_state_t *state, void *user_data) {
    td_finished_custom(
        ACTION_TAP_DANCE_CUSTOM(
            ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_V)),
            ACTION_TAP_DANCE_CONFIG_FN(sendPw),
            ACTION_TAP_DANCE_CONFIG_KEY(SGUI(KC_Z)),
            ACTION_TAP_DANCE_CONFIG_FN(surprise),
            ACTION_TAP_DANCE_CONFIG_KEY(KC_NO),
            ACTION_TAP_DANCE_CONFIG_KEY(KC_NO)
        ),
        &td_two_tap_state,
        state,
        user_data
    );
}
void two_reset(tap_dance_state_t *state, void *user_data) {
    td_reset_custom(
        ACTION_TAP_DANCE_CUSTOM(
            ACTION_TAP_DANCE_CONFIG_KEY(LGUI(KC_V)),
            ACTION_TAP_DANCE_CONFIG_FN(sendPw),
            ACTION_TAP_DANCE_CONFIG_KEY(SGUI(KC_Z)),
            ACTION_TAP_DANCE_CONFIG_FN(surprise),
            ACTION_TAP_DANCE_CONFIG_KEY(KC_NO),
            ACTION_TAP_DANCE_CONFIG_KEY(KC_NO)
        ),
        &td_two_tap_state,
        state,
        user_data
    );
}

tap_dance_action_t tap_dance_actions[] = {
  [T_ONE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, one_finished, one_reset),
  [T_TWO]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, two_finished, two_reset),
};
