#pragma once
enum {
  T_SSPW,
  T_DL_HS,
  T_SCOPE,
};

#define SCRN_S       LGUI(LSFT(KC_4))
#define SCRN_C       LCTL(SCRN_S)

#define TD_SSPW      TD(T_SSPW)
#define TD_DL_HS     TD(T_DL_HS)
#define TD_SCOPE     TD(T_SCOPE)

void matrix_scan_tap_dance(void);
void tap_dance_ss(TD_ARGS);
void tap_dance_scope(TD_ARGS);
