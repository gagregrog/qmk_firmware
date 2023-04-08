#include QMK_KEYBOARD_H
#pragma once

enum userspace_layers {
  _LAYER_COLEMAK_DH = 0,
  _LAYER_QWERTY,
  _LAYER_NUM,
  _LAYER_UTIL,
  _LAYER_SETTINGS
};

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

#if defined(TRACKPOINT_ENABLE)
  #define TRACKPT KC_NO
  #define MS_SCL_P MOUSE_SCROLL_PRESS
  #define MS_SCL_L MOUSE_SCROLL_LOCK
  #define MS_TGGL  MOUSE_TOGGLE
#endif // TRACKPOINT_ENABLE

/**
 * Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for CAGS (Ctl, Alt, Gui, Shift)
 * home row mods.  The layout passed in parameter must contain at least 20 keycodes.
 * Applies HRMs to the second row of the 10-key rows provided
 *
 * This is meant to be used with a layer define defined previously, eg.:
 *
 *     HOME_ROW_MOD_CAGS(LAYOUT_LAYER_BASE_COLEMAK_DH)
 */
#define _HOME_ROW_MOD_CAGS(                                                                                                                          \
  L00,          L01,          L02,          L03,          L04,               R05,          R06,          R07,          R08,          R09,            \
  L10,          L11,          L12,          L13,          L14,               R15,          R16,          R17,          R18,          R19,            \
...)                                                                                                                                                 \
  L00,          L01,          L02,          L03,          L04,               R05,          R06,          R07,          R08,          R09,            \
  LCTL_T(L10),  LALT_T(L11),  LGUI_T(L12),  LSFT_T(L13),  L14,               R15,          RSFT_T(R16),  RGUI_T(R17),  LALT_T(R18),  RCTL_T(R19),    \
__VA_ARGS__

#define HOME_ROW_MOD_CAGS(...) _HOME_ROW_MOD_CAGS(__VA_ARGS__)

#define TG_BASE  BASE_TOGGLE
// layer switches
#define NUM_GRV  LT(_LAYER_NUM, KC_GRV)
#define UTIL_MN  LT(_LAYER_UTIL, KC_MINS)
#define MO_SETS  MO(_LAYER_SETTINGS)

#if defined(USE_LAYOUT_3x5_3)
#define LAYOUT_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

#define _LAYOUT_split_3x5_3_base( \
  L00, L01, L02, L03, L04,     R05, R06, R07, R08, R09, \
  L10, L11, L12, L13, L14,     R15, R16, R17, R18, R19, \
  L20, L21, L22, L23, L24,     R25, R26, R27, R28, R29  \
) \
    L00,     L01,     L02,     L03,     L04,               R05,     R06,     R07,     R08,     R09, \
    L10,     L11,     L12,     L13,     L14,               R15,     R16,     R17,     R18,     R19, \
    L20,     L21,     L22,     L23,     L24,               R25,     R26,     R27,     R28,     R29, \
                      KC_SPC,  KC_BSPC, NUM_GRV,           UTIL_MN, KC_DLR,  KC_ENT

#define LAYOUT_split_3x5_3_base(...) _LAYOUT_split_3x5_3_base(__VA_ARGS__)

#define ______________COLEMAK_MOD_DH_L1____________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define ______________COLEMAK_MOD_DH_L2____________       KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#define ______________COLEMAK_MOD_DH_L3____________       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V

#define ______________COLEMAK_MOD_DH_R1____________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT
#define ______________COLEMAK_MOD_DH_R2____________       KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#define ______________COLEMAK_MOD_DH_R3____________       KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLASH

#define _________________QWERTY_L1_________________       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________       KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________NUMERIC_L1________________       KC_TAB,  KC_NO,   KC_UP,   KC_NO,   KC_GRV
#define _________________NUMERIC_L2________________       KC_ESC,  KC_LEFT, KC_DOWN, KC_RIGHT,KC_NO
#define _________________NUMERIC_L3________________       KC_NO,   KC_BTN1, KC_BTN3, KC_BTN2, KC_NO

#define _________________NUMERIC_R1________________       KC_LPRN, KC_7,    KC_8,    KC_9,    KC_PIPE
#define _________________NUMERIC_R2________________       KC_LBRC, KC_4,    KC_5,    KC_6,    KC_SCLN
#define _________________NUMERIC_R3________________       KC_LCBR, KC_1,    KC_2,    KC_3,    KC_BSLS

#define _________________UTILITY_L1________________       KC_LCBR, XXXXXXX, XXXXXXX, KC_MPLY, KC_VOLU
#define _________________UTILITY_L2________________       KC_LBRC, XXXXXXX, XXXXXXX, KC_MNXT, KC_VOLD
#define _________________UTILITY_L3________________       KC_LPRN, XXXXXXX, XXXXXXX, KC_MPRV, KC_MUTE

#define _________________UTILITY_R1________________       XXXXXXX, MV_UL,   MV_U,    MV_UR,   KC_RCBR
#define _________________UTILITY_R2________________       XXXXXXX, MV_L,    MV_C,    MV_R,    KC_RBRC
#define _________________UTILITY_R3________________       XXXXXXX, MV_DL,   MV_D,    MV_DR,   KC_RPRN

#define _________________NOPE_X5___________________       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define LAYOUT_COLEMAK_DH LAYOUT_split_3x5_3_base(                                                            \
        ______________COLEMAK_MOD_DH_L1____________,         ______________COLEMAK_MOD_DH_R1____________,     \
        ______________COLEMAK_MOD_DH_L2____________,         ______________COLEMAK_MOD_DH_R2____________,     \
        ______________COLEMAK_MOD_DH_L3____________,         ______________COLEMAK_MOD_DH_R3____________      \
)

#define LAYOUT_QWERTY LAYOUT_split_3x5_3_base(                                                                \
        _________________QWERTY_L1_________________,         _________________QWERTY_R1_________________,     \
        _________________QWERTY_L2_________________,         _________________QWERTY_R2_________________,     \
        _________________QWERTY_L3_________________,         _________________QWERTY_R3_________________      \
)

#define LAYOUT_NUMERIC                                                                                        \
        _________________NUMERIC_L1________________,          _________________NUMERIC_R1________________,    \
        _________________NUMERIC_L2________________,          _________________NUMERIC_R2________________,    \
        _________________NUMERIC_L3________________,          _________________NUMERIC_R3________________,    \
                          KC_NO,   KC_NO,   _______,          KC_EQL,  KC_0,    KC_PDOT                       \

#define LAYOUT_UTILITY                                                                                        \
        _________________UTILITY_L1________________,          _________________UTILITY_R1________________,    \
        _________________UTILITY_L2________________,          _________________UTILITY_R2________________,    \
        _________________UTILITY_L3________________,          _________________UTILITY_R3________________,    \
                          XXXXXXX, XXXXXXX, MO_SETS,          _______, XXXXXXX, XXXXXXX

#define LAYOUT_SETTINGS                                                                                       \
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG_BASE,    \
        _________________NOPE_X5___________________,          _________________NOPE_X5___________________,    \
        _________________NOPE_X5___________________,          _________________NOPE_X5___________________,    \
                          XXXXXXX, XXXXXXX, _______,          _______, XXXXXXX, XXXXXXX

#endif // USE_LAYOUT_3x5_3
