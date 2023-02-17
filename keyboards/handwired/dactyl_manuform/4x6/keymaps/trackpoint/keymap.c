#include QMK_KEYBOARD_H
#include "features/mouse_turbo_click.h"

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
  T_SSPW,
  T_DL_HS,
  T_SCOPE,
};

#define TD_SSPW      TD(T_SSPW)
#define TD_DL_HS     TD(T_DL_HS)
#define TD_SCOPE     TD(T_SCOPE)

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


enum layers {
  _BASE,
  _NUMPAD,
  _MEDIA,
  _WINDOW,
  _MOUSE,
  _GAME,
  _RESET,
};

// layer switches
#define NUMPAD    TT(_NUMPAD)
#define MEDIA     TT(_MEDIA)
#define BASE      TT(_BASE)
#define TO_BASE   TO(_BASE)
#define WINDOW    TT(_WINDOW)
#define GAME      TO(_GAME)
#define MS_GRV    LT(_MOUSE, KC_GRV)
#define MO_RST    MO(_RESET)

#define CMD_ESC   LGUI_T(KC_ESC)
#define VOICE     LGUI(KC_F5)

#define MV_UL     HYPR(KC_UP)
#define MV_U      LCAG(KC_UP)
#define MV_UR     HYPR(KC_RIGHT)
#define MV_R      LCAG(KC_RIGHT)
#define MV_C      HYPR(KC_ENT)
#define MV_L      LCAG(KC_LEFT)
#define MV_DL     HYPR(KC_LEFT)
#define MV_D      LCAG(KC_DOWN)
#define MV_DR     HYPR(KC_DOWN)

#define SCRN_S    LGUI(LSFT(KC_4))
#define SCRN_C    LCTL(SCRN_S)
#define DUP       LGUI(LSFT(KC_D))
#define ROW       LGUI(LSFT(KC_ENTER))

#define COPY      LGUI(KC_C)
#define PASTE     LGUI(KC_V)
#define CUT       LGUI(KC_X)
#define UNDO      LGUI(KC_Z)
#define NEXT      LGUI(KC_D)
#define SAVE      LGUI(KC_S)

// Left-hand home row mods - _BASE layer
#define CTRL_A    LCTL_T(KC_A)
#define ALT_R     LALT_T(KC_R)
#define GUI_S     LGUI_T(KC_S)
#define SHFT_T    LSFT_T(KC_T)

// Right-hand home row mods - _BASE layer
#define SHFT_N    RSFT_T(KC_N)
#define GUI_E     RGUI_T(KC_E)
#define ALT_I     LALT_T(KC_I)
#define CTRL_O    RCTL_T(KC_O)

// Left-hand home row mods - _NUMPAD layer
// #define CTRL_A    LCTL_T(KC_A)
#define ALT_LEFT  LALT_T(KC_LEFT)
#define GUI_DOWN  LGUI_T(KC_DOWN)
#define SHFT_RGT  LSFT_T(KC_RIGHT)

// Right-hand home row mods - _NUMPAD layer
#define SHFT_4    RSFT_T(KC_4)
#define GUI_5     RGUI_T(KC_5)
#define ALT_6     LALT_T(KC_6)
#define CTRL_PLS  RCTL_T(KC_PMNS)

#define TRACKPT KC_NO

uint32_t last_light_mode;

enum custom_keycodes {
  MOUSE_SCROLL_PRESS = SAFE_RANGE,
  MOUSE_SCROLL_LOCK,
  MOUSE_TOGGLE,
  MOUSE_REPEAT,
};

#define MS_SCL_P MOUSE_SCROLL_PRESS
#define MS_SCL_L MOUSE_SCROLL_LOCK
#define MS_TGGL  MOUSE_TOGGLE
#define MS_RPT   MOUSE_REPEAT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (colmak dh mod)
     * +-----------------------------------------+                             +-----------------------------------------+
     * | TAB  |   q  |   w  |   f  |   p  |   b  |                             |   j  |   l  |   u  |   y  |   p  |  ;   |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |CMDESC|   a  |   r  |   s  |   t  |   g  |                             |   m  |   n  |   e  |   i  |   o  |CMD/' |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | SHFT |   z  |   x  |   c  |   d  |   v  |                             |   k  |   h  |   ,  |   .  |   /  | SHFT |
     * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
     *               |  [   |   ]  |                                                         |   {  |  }   |
     *               +-------------+-------------+                             +-------------+-------------+
     *                             | SPACE|BCKSPC|                             |  =/+ |  ENT |
     *                             +-------------+                             +-------------+
     *                                           +-------------+ +-------------+
     *                                           |   `~ |NUMPAD | |MEDIA |   -  |
     *                                           |------+------| |------+------|
     *                                           | LEFT |RIGHT | |  UP  |DOWN  |
     *                                           +-------------+ +-------------+
     */
    [_BASE] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, TD_SSPW,
        CMD_ESC, CTRL_A,  ALT_R,   GUI_S,   SHFT_T,  KC_G,                KC_M,    SHFT_N,  GUI_E,   ALT_I,   CTRL_O,  KC_SCLN,
        SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC,
                          KC_LBRC, KC_RBRC,                                                 KC_LCBR, KC_RCBR,
                                            KC_SPC,  KC_BSPC,             TRACKPT, KC_ENT,
                                            MS_GRV,  NUMPAD,              KC_EQL,  KC_MINS,
                                            MS_SCL_P,MS_SCL_L,            MEDIA,   TD_DL_HS
    ),

    [_NUMPAD] = LAYOUT(
        RGB_VAD, RGB_VAI, RGB_RMOD,KC_UP,   RGB_MOD, RGB_TOG,             VOICE,   KC_7,    KC_8,    KC_9,    KC_PSLS, KC_PAST,
        _______, KC_LCTL, ALT_LEFT,GUI_DOWN,SHFT_RGT,KC_NO,               KC_NO,   SHFT_4,  GUI_5,   ALT_6,   CTRL_PLS,KC_PPLS,
        _______, UNDO,    CUT,     COPY,    NEXT,    PASTE,               KC_NO,   KC_1,    KC_2,    KC_3,    KC_BSLS, KC_PIPE,
                          KC_NO,   KC_NO,                                                   KC_0,    KC_PDOT,
                                            _______, _______,             TRACKPT, ROW,
                                            _______, _______,             DUP,     KC_RALT,
                                            _______, _______,             WINDOW,  KC_HASH
    ),

    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, MS_TGGL,             _______, _______, KC_WH_D, _______, _______, _______,
        _______, _______, KC_BTN1, KC_BTN3, KC_BTN2, _______,             _______, KC_WH_L, KC_WH_U, KC_WH_R, _______, _______,
        _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
                          _______, _______,                                                 _______, _______,
                                            _______, _______,             TRACKPT, _______,
                                            _______, _______,             _______, GAME,
                                            _______, _______,             _______, _______
    ),

    [_GAME] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_GRV,  KC_ESC,
        KC_J,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                KC_NO,   KC_BTN1, KC_BTN3, KC_BTN2, KC_NO,   KC_NO,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                KC_NO,   KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, KC_NO,
                          KC_ESC,  KC_ESC,                                                  KC_NO,   KC_NO,
                                            KC_SPC,  MS_RPT,              TRACKPT, KC_ENT,
                                            KC_COMM, TD_SCOPE,            KC_EQL,  KC_MINS,
                                            KC_SLSH, KC_MINS,             KC_NO,   TO_BASE
    ),

    [_MEDIA] = LAYOUT(
        KC_NO,   KC_NO,   MV_UL,   MV_U,    MV_UR,   KC_WH_U,             KC_NO,   KC_VOLD, KC_MUTE, KC_VOLU, KC_NO,   KC_NO,
        KC_NO,   KC_NO,   MV_L,    MV_C,    MV_R,    KC_WH_D,             KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   KC_NO,
        KC_NO,   KC_NO,   MV_DL,   MV_D,    MV_DR,   KC_NO,               KC_NO,   KC_NO,   KC_MSTP, KC_NO,   KC_NO,   KC_NO,
                          KC_NO,   KC_NO,                                                   KC_NO,   KC_NO,
                                            _______, CW_TOGG,             TRACKPT, _______,
                                            KC_NO,   WINDOW,              KC_NO,   KC_NO,
                                            _______, _______,             _______, MO_RST
    ),

    [_WINDOW] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   MV_UL,   MV_U,     MV_UR,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   MV_L,    MV_C,     MV_R,    KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   MV_DL,   MV_D,     MV_DR,   KC_NO,   KC_NO,
                          KC_NO,   KC_NO,                                                   KC_NO,    KC_NO,
                                            KC_NO,   KC_NO,               TRACKPT, KC_NO,
                                            KC_NO,   _______,             KC_NO,   KC_NO,
                                            KC_NO,   BASE,                _______, KC_NO
    ),

    [_RESET] = LAYOUT(
        QK_BOOT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
                          KC_NO,   KC_NO,                                                   KC_NO,   KC_NO,  
                                            KC_NO,   KC_NO,               TRACKPT, KC_NO,  
                                            KC_NO,   KC_NO,               KC_NO,   KC_NO,  
                                            KC_NO,   KC_NO,               KC_NO,   _______
    )
};

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

void matrix_init_user(void) {
  rgblight_enable();
};

layer_state_t layer_state_set_user(layer_state_t state) {
  uint32_t current_light_mode = rgblight_get_mode();

  // if we're switching away from a color mode, store it
  if (current_light_mode != RGBLIGHT_MODE_STATIC_LIGHT) {
    last_light_mode = current_light_mode;
  }

  switch (biton32(state)) {
    case _BASE:
      rgblight_mode_noeeprom(last_light_mode);
      break;
    case _MEDIA:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_PURPLE);
      break;
    case _NUMPAD:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_GREEN);
      break;
    case _WINDOW:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_MAGENTA);
      break;
    case _MOUSE:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_TEAL);
      break;
    case _GAME:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_CHARTREUSE);
      break;
    case _RESET:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_RED);
      break;
    default: //  for any other layers, or the default layer
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_ORANGE);
      break;
  }
  return state;
}

void keyboard_post_init_user(void) {
  rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
  rgblight_sethsv(HSV_ORANGE);
  last_light_mode = RGBLIGHT_MODE_RAINBOW_SWIRL;
}

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicative that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currently not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustrating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
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

static td_tap_t sspw_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

static td_tap_t scope_tap_state = {
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

void sendPW(void) {
  SEND_STRING("password1");
};

void sendTraveler(void) {
  SEND_STRING("v4_traveler@nge.com");
};

uint16_t bf_scope_timer = 0;

void start_scope(void) {
  if (!bf_scope_timer) {
    bf_scope_timer = timer_read();
    register_code(KC_DOT);
  }
}

void sspw_finished(tap_dance_state_t *state, void *user_data) {
  finished_quad(ACTION_TAP_DANCE_QUAD(ACTION_TAP_DANCE_CONFIG_KEY(SCRN_C), ACTION_TAP_DANCE_CONFIG_KEY(SCRN_S), ACTION_TAP_DANCE_CONFIG_FN(sendPW), ACTION_TAP_DANCE_CONFIG_FN(sendTraveler)), &sspw_tap_state, state, user_data);
}
void sspw_reset(tap_dance_state_t *state, void *user_data) {
  reset_quad(ACTION_TAP_DANCE_QUAD(ACTION_TAP_DANCE_CONFIG_KEY(SCRN_C), ACTION_TAP_DANCE_CONFIG_KEY(SCRN_S), ACTION_TAP_DANCE_CONFIG_FN(sendPW), ACTION_TAP_DANCE_CONFIG_FN(sendTraveler)), &sspw_tap_state, state, user_data);
}

void scope_finished(tap_dance_state_t *state, void *user_data) {
  finished_quad(ACTION_TAP_DANCE_QUAD(ACTION_TAP_DANCE_CONFIG_FN(start_scope), ACTION_TAP_DANCE_CONFIG_KEY(KC_DOT), ACTION_TAP_DANCE_CONFIG_FN(start_scope), ACTION_TAP_DANCE_CONFIG_KEY(KC_DOT)), &scope_tap_state, state, user_data);
}
void scope_reset(tap_dance_state_t *state, void *user_data) {
  reset_quad(ACTION_TAP_DANCE_QUAD(ACTION_TAP_DANCE_CONFIG_FN(start_scope), ACTION_TAP_DANCE_CONFIG_KEY(KC_DOT), ACTION_TAP_DANCE_CONFIG_FN(start_scope), ACTION_TAP_DANCE_CONFIG_KEY(KC_DOT)), &scope_tap_state, state, user_data);
}

tap_dance_action_t tap_dance_actions[] = {
  [T_SSPW]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sspw_finished, sspw_reset),
  [T_DL_HS]  = ACTION_TAP_DANCE_DOUBLE(KC_DLR, KC_HASH),
  [T_SCOPE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scope_finished, scope_reset),
};

bool msScrollPress = false;
bool msScrollLock = false;
bool msEnabled = true;
uint8_t mouseCount = 0;
uint8_t mouseDebounce = 3;
bool firstMouseReportIgnored = false;

void rotate_mouse_report(report_mouse_t *mouse_report) {
  // https://doubleroot.in/lessons/coordinate-geometry-basics/rotation-of-axes/
  // theta = -pi/4
  const double cos_theta = 0.7071067811865475;
  const double sin_theta = -0.7071067811865475;
  double x_cos = cos_theta * mouse_report->x;
  double y_cos = cos_theta * mouse_report->y;
  double x_sin = sin_theta * mouse_report->x;
  double y_sin = sin_theta * mouse_report->y;
  double x = x_cos - y_sin;
  double y = x_sin + y_cos;
  mouse_report->x = (mouse_xy_report_t) x;
  mouse_report->y = (mouse_xy_report_t) y;
}

void ignoreMouseReport(report_mouse_t *mouse_report) {
  mouse_report->x = 0;
  mouse_report->y = 0;
  mouse_report->h = 0;
  mouse_report->v = 0;
  mouse_report->buttons = 0;
}

void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
  if (!firstMouseReportIgnored) {
    // first report always does a right click and jumps the cursor,
    // so let's ignore it
    firstMouseReportIgnored = true;
    ignoreMouseReport(mouse_report);
    return;
  }

  if (!msEnabled) {
    ignoreMouseReport(mouse_report);
    return;
  }

  // rotate_mouse_report(mouse_report);

  // process special mouse mode whether pressed or locked
  bool lockActive = msScrollLock && !msScrollPress;
  bool pressActive = !msScrollLock && msScrollPress;
  bool mouseScrollActive = (lockActive || pressActive);

  // only handle special mouse modes when enabled by press or lock
  if (!mouseScrollActive) {
    return;
  }

  // debounce mouse mode actions so it is more controllable
  if (mouseCount > mouseDebounce) {
    mouseCount = 0;
  }

  // only register mouse mode behavior once every mouseDebounce times
  if (!mouseCount) {
    // reassign normal mouse movement to scroll movement
    mouse_report->h = mouse_report->x / -3;
    mouse_report->v = mouse_report->y / -3;
  }
  
  // disable normal mouse movement
  // must happen after reassigning the movement above
  mouse_report->x = 0;
  mouse_report->y = 0;

  // increment counter to limit scroll processing
  mouseCount++;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_mouse_turbo_click(keycode, record, MS_RPT)) { return false; }

  switch (keycode) {
    case MOUSE_SCROLL_PRESS:
      msScrollPress = record->event.pressed;
      return false; // Skip all further processing of this key
    case MOUSE_SCROLL_LOCK:
      if (record->event.pressed) {
        msScrollLock = !msScrollLock;
      }
      return false;
    case MOUSE_TOGGLE:
      if (record->event.pressed) {
        msEnabled = !msEnabled;
      }
      return false;
    default:
      return true; // Process all other keycodes normally
  }
}

void matrix_scan_user(void) {
  if (bf_scope_timer && timer_elapsed(bf_scope_timer) > 200) {
    tap_code(KC_G);
    unregister_code(KC_DOT);
    bf_scope_timer = 0;
  }
}
