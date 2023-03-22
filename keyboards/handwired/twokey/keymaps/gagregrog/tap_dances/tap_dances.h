#include "gagregrog.h"

// screenshot to clipboard
#define SCRN_C      LCTL(SGUI(KC_4))
#define SCRN_S      SGUI(KC_4)
#define KC_OS_LOCK  LCTL(LGUI(KC_Q))

enum tap_dance_keys {
  T_ONE,
  T_TWO,
};

#define TD_ONE     TD(T_ONE)
#define TD_TWO     TD(T_TWO)
