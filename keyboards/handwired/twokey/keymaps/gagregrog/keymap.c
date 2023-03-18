#include QMK_KEYBOARD_H
#include "gagregrog.h"
#include "tap_dances/tap_dances.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_1x2(TD_ONE, TD_TWO)
};
