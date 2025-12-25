#include QMK_KEYBOARD_H

#define ESC_DURATION 6000
#define RET_DURATION 6000

enum {
    TD_ESC_SPECIAL,
    TD_RET_SPECIAL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TD(TD_ESC_SPECIAL),
        TD(TD_RET_SPECIAL),
        KC_BTN2
    )
};

static bool esc_hold_active = false;
static bool esc_physically_held = false;
static uint16_t esc_timer = 0;

static bool ret_hold_active = false;
static bool ret_physically_held = false;
static uint16_t ret_timer = 0;

void matrix_scan_kb(void) {
    if (esc_hold_active && timer_elapsed(esc_timer) > ESC_DURATION) {
        unregister_code(KC_ESC);
        esc_hold_active = false;
    }

    if (ret_hold_active && timer_elapsed(ret_timer) > RET_DURATION) {
        unregister_code(KC_RETN);
        ret_hold_active = false;
    }
}

void esc_tap_dance_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            // Press-and-hold: behave like a normal Esc hold
            register_code(KC_ESC);
            esc_physically_held = true;
        } else {
            // Single tap
            tap_code(KC_ESC);
        }
    } else if (state->count == 2) {
        // Double tap: hold Esc for ESC_DURATION seconds
        register_code(KC_ESC);
        esc_timer = timer_read();
        esc_hold_active = true;
    }
}

void esc_tap_dance_reset(tap_dance_state_t *state, void *user_data) {
    if (esc_physically_held) {
        unregister_code(KC_ESC);
        esc_physically_held = false;
    }
}

void ret_tap_dance_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            // Press-and-hold: behave like a normal return hold
            register_code(KC_RETN);
            ret_physically_held = true;
        } else {
            // Single tap
            tap_code(KC_RETN);
        }
    } else if (state->count == 2) {
        // Double tap: hold Return for RET_DURATION seconds
        register_code(KC_RETN);
        ret_timer = timer_read();
        ret_hold_active = true;
    }
}

void ret_tap_dance_reset(tap_dance_state_t *state, void *user_data) {
    if (ret_physically_held) {
        unregister_code(KC_RETN);
        ret_physically_held = false;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_SPECIAL] = ACTION_TAP_DANCE_FN_ADVANCED(
        NULL,
        esc_tap_dance_finished,
        esc_tap_dance_reset
    ),
    [TD_RET_SPECIAL] = ACTION_TAP_DANCE_FN_ADVANCED(
        NULL,
        ret_tap_dance_finished,
        ret_tap_dance_reset
    ),
};
