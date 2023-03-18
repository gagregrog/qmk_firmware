#pragma once
#include QMK_KEYBOARD_H

#if defined(OLED_ENABLE)
  #include "oled/oled_util.h"
#endif // OLED_ENABLE

#if defined(MOUSE_TURBO_CLICK)
  #include "mouse_turbo_click/mouse_turbo_click.h"
#endif // MOUSE_TURBO_CLICK

#if defined(TAP_DANCE_ENABLE)
  #include "tap_dance/tap_dance_utils.h"
#endif // TAP_DANCE_ENABLE

// windowing shortcuts
#define MV_UL     HYPR(KC_UP)
#define MV_U      LCAG(KC_UP)
#define MV_UR     HYPR(KC_RIGHT)
#define MV_R      LCAG(KC_RIGHT)
#define MV_C      HYPR(KC_ENT)
#define MV_L      LCAG(KC_LEFT)
#define MV_DL     HYPR(KC_LEFT)
#define MV_D      LCAG(KC_DOWN)
#define MV_DR     HYPR(KC_DOWN)

#if defined(POINTING_DEVICE_ENABLE)
report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report);
#endif // POINTING_DEVICE_ENABLE

enum gagregrog_keycodes {
#if defined(DILEMMA_SAFE_RANGE)
  BASE_TOGGLE = DILEMMA_SAFE_RANGE,
#else
  BASE_TOGGLE = SAFE_RANGE,
#endif // DILEMMA_SAFE_RANGE
#if defined(MOUSE_TURBO_CLICK)
  MS_TURBO,
#endif // MOUSE_TURBO_CLICK
#if defined(TRACKPOINT_ENABLE)
  MOUSE_SCROLL_PRESS,
  MOUSE_SCROLL_LOCK,
  MOUSE_TOGGLE,
#endif // TRACKPOINT_ENABLE
#if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
  KC_SECRET_1,
  KC_SECRET_2,
  KC_SECRET_3,
  KC_SECRET_4,
  KC_SECRET_5,
#endif
  NEW_SAFE_RANGE,
};

#if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
  // define this so it can be used in tapdances
  void send_secret(uint16_t keycode);
#endif

#if defined(TRACKPOINT_ENABLE)
  #define TRACKPT KC_NO
  #define MS_SCL_P MOUSE_SCROLL_PRESS
  #define MS_SCL_L MOUSE_SCROLL_LOCK
  #define MS_TGGL  MOUSE_TOGGLE
#endif // TRACKPOINT_ENABLE

#if defined(USE_LAYOUT_3x5) || defined(USE_LAYOUT_3x5_3)
/**
 * Convenience macro to auto-prefix KC_ to provided keys for the primary keys on a 3x5 layout
 *
 * Expects a 10-key per row layout.
 * The layout passed in parameter must contain at least 20 keycodes.
 *
 */
#define _KC_LAYOUT_3x5_wrapper(                                                                         \
         k00,      k01,      k02,      k03,      k04,      k05,      k06,      k07,      k08,      k09, \
         k10,      k11,      k12,      k13,      k14,      k15,      k16,      k17,      k18,      k19, \
         k20,      k21,      k22,      k23,      k24,      k25,      k26,      k27,      k28,      k29, \
...)                                                                                                    \
    KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06, KC_##k07, KC_##k08, KC_##k09, \
    KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k16, KC_##k17, KC_##k18, KC_##k19, \
    KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25, KC_##k26, KC_##k27, KC_##k28, KC_##k29, \
    __VA_ARGS__

#define KC_LAYOUT_3x5_wrapper(...) _KC_LAYOUT_3x5_wrapper(__VA_ARGS__)

/**
 * Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for CAGS (Ctl, Alt, Gui, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with a layer define defined above, eg.:
 *
 *     HOME_ROW_MOD_CAGS_3x5(LAYOUT_LAYER_BASE_COLEMAK_DH)
 */
#define _HOME_ROW_MOD_CAGS_3x5(                                                         \
        L00, L01, L02, L03, L04,        R05, R06, R07, R08, R09,                        \
        L10, L11, L12, L13, L14,        R15, R16, R17, R18, R19,                        \
...)                                                                                    \
        L00,            L01,            L02,            L03,            L04,            \
        R05,            R06,            R07,            R08,            R09,            \
        LCTL_T(L10),    LALT_T(L11),    LGUI_T(L12),    LSFT_T(L13),    L14,            \
        R15,            RSFT_T(R16),    RGUI_T(R17),    LALT_T(R18),    RCTL_T(R19),    \
      __VA_ARGS__

#define HOME_ROW_MOD_CAGS_3x5(...) _HOME_ROW_MOD_CAGS_3x5(__VA_ARGS__)

#if defined(USE_LAYOUT_3x5_3)

#define LAYOUT_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

enum gagregrog_3x5_layers {
  LAYER_BASE_COLEMAK_MOD_DH = 0,
  LAYER_BASE_QWERTY,
  LAYER_NUM,
  LAYER_UTIL,
  LAYER_SETTINGS,
};

// custom keys
#define TG_BASE  BASE_TOGGLE

// layer switches
#define NUM_GRV  LT(LAYER_NUM, KC_GRV)
#define UTIL_MN  LT(LAYER_UTIL, KC_MINS)
#define MO_SETS  MO(LAYER_SETTINGS)

#define LAYOUT_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

#define LAYOUT_COLEMAK_MOD_DH_BASE KC_LAYOUT_3x5_wrapper(                                                     \
        Q,       W,       F,       P,       B,                J,       L,       U,       Y,       QUOT,       \
        A,       R,       S,       T,       G,                M,       N,       E,       I,       O,          \
        Z,       X,       C,       D,       V,                K,       H,       COMM,    DOT,     SLASH,      \
                          KC_SPC,  KC_BSPC, NUM_GRV,          UTIL_MN, KC_DLR,  KC_ENT                        \
)

#define LAYOUT_QWERTY_BASE KC_LAYOUT_3x5_wrapper(                                                             \
        Q,       W,       E,       R,       T,                Y,       U,       I,       O,       P,          \
        A,       S,       D,       F,       G,                H,       J,       K,       L,       SCLN,       \
        Z,       X,       C,       V,       B,                N,       M,       COMM,    DOT,     SLASH,      \
                          KC_SPC,  KC_BSPC, NUM_GRV,          UTIL_MN, KC_DLR,  KC_ENT                        \
)

#define LAYOUT_NUMERIC KC_LAYOUT_3x5_wrapper(                                                                 \
        TAB,     NO,      UP,      NO,      GRV,              LPRN,    7,       8,       9,       PIPE,       \
        ESC,     LEFT,    DOWN,    RIGHT,   NO,               LBRC,    4,       5,       6,       SCLN,       \
        NO,      BTN1,    BTN3,    BTN2,    NO,               LCBR,    1,       2,       3,       BSLS,       \
                          KC_NO,   KC_NO,   _______,          KC_EQL,  KC_0,    KC_PDOT                       \
)

#define LAYOUT_UTILITY                                                                                        \
        KC_LCBR, XXXXXXX, XXXXXXX, KC_MPLY, KC_VOLU,          XXXXXXX, MV_UL,   MV_U,    MV_UR,   KC_RCBR,    \
        KC_LBRC, XXXXXXX, XXXXXXX, KC_MNXT, KC_VOLD,          XXXXXXX, MV_L,    MV_C,    MV_R,    KC_RBRC,    \
        KC_LPRN, XXXXXXX, XXXXXXX, KC_MPRV, KC_MUTE,          XXXXXXX, MV_DL,   MV_D,    MV_DR,   KC_RPRN,    \
                          XXXXXXX, XXXXXXX, MO_SETS,          _______, XXXXXXX, XXXXXXX

#define LAYOUT_SETTINGS                                                                                       \
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG_BASE,    \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    \
                          XXXXXXX, XXXXXXX, _______,          _______, XXXXXXX, XXXXXXX

#endif // USE_LAYOUT_3x5_3

#endif // USE_LAYOUT_3x5 || USE_LAYOUT_3x5_3
