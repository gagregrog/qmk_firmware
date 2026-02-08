#include QMK_KEYBOARD_H

#define ESC_DURATION 6000
#define RET_DURATION 6000
#define BTN_DURATION 6000

enum {
    TD_ESC_SPECIAL,
    TD_RET_SPECIAL,
    TD_BTN_SPECIAL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TD(TD_ESC_SPECIAL),
        TD(TD_RET_SPECIAL),
        TD(TD_BTN_SPECIAL)
    )
};

static bool esc_hold_active = false;
static bool esc_physically_held = false;
static uint16_t esc_timer = 0;

static bool ret_hold_active = false;
static bool ret_physically_held = false;
static uint16_t ret_timer = 0;

static bool btn_hold_active = false;
static bool btn_physically_held = false;
static uint16_t btn_timer = 0;

void matrix_scan_kb(void) {
    if (esc_hold_active && timer_elapsed(esc_timer) > ESC_DURATION) {
        unregister_code(KC_ESC);
        esc_hold_active = false;
    }

    if (ret_hold_active && timer_elapsed(ret_timer) > RET_DURATION) {
        unregister_code(KC_RETN);
        ret_hold_active = false;
    }

    if (btn_hold_active && timer_elapsed(btn_timer) > BTN_DURATION) {
        unregister_code(MS_BTN1);
        btn_hold_active = false;
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

void btn_tap_dance_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            // Press-and-hold: behave like a normal mouse button hold
            register_code(MS_BTN1);
            btn_physically_held = true;
        } else {
            // Single tap
            tap_code(MS_BTN1);
        }
    } else if (state->count == 2) {
        // Double tap: hold mouse button for BTN_DURATION seconds
        register_code(MS_BTN1);
        btn_timer = timer_read();
        btn_hold_active = true;
    } else if (state->count == 3) {
        if (state->pressed) {
            // enter bootloader mode for flashing
            reset_keyboard();
        } 
    }
}

void btn_tap_dance_reset(tap_dance_state_t *state, void *user_data) {
    if (btn_physically_held) {
        unregister_code(MS_BTN1);
        btn_physically_held = false;
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
    [TD_BTN_SPECIAL] = ACTION_TAP_DANCE_FN_ADVANCED(
        NULL,
        btn_tap_dance_finished,
        btn_tap_dance_reset
    ),
};
