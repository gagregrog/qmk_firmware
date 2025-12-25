#include QMK_KEYBOARD_H

#define ESC_DURATION 10000

enum custom_keycodes {
    ESC_HOLD = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        ESC_HOLD,
        KC_BTN1,
        KC_BTN2
    )
};

static bool esc_hold_active = false;
static uint16_t esc_timer = 0;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ESC_HOLD:
            if (record->event.pressed && !esc_hold_active) {
                // Press and hold Escape
                register_code(KC_ESC);
                esc_timer = timer_read();
                esc_hold_active = true;
            }
            return false; // We handled it fully
    }
    return true;
}

void matrix_scan_kb(void) {
    if (esc_hold_active && timer_elapsed(esc_timer) > ESC_DURATION) {
        unregister_code(KC_ESC);
        esc_hold_active = false;
    }
}
