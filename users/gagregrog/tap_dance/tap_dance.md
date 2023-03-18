# Tap Dance

When Tap Dances are enabled, these utilities will be exposed automatically. The setup is still pretty extensive, but these utilities will help. Currently it allows you to define key taps/holds for KC_ keycodes, user defined functions, and KC_Secrets.

## Configuration

In your `keymap.c`, first create an enum to hold all of your tap dances and then for convenience create defines for some new keycodes to use in your layout.

```c
enum tap_dance_keys {
  T_MY_DANCE,
};

#define TD_MY_DANCE     TD(T_MY_DANCE)
```

For each tap dance you will need to create a state container that looks like this:

```c
static td_tap_t td_my_dance_state = {
  .is_press_action = true,
  .state = TD_NONE
};
```

And then create some defines that hold your tap dance configurations. For these, we expose the macros `ACTION_TAP_DANCE_CUSTOM` which accepts 6 different actions. The actions must be wrapped in either `ACTION_TAP_DANCE_CONFIG_KEY` or `ACTION_TAP_DANCE_CONFIG_FN`. `ACTION_TAP_DANCE_CONFIG_KEY` accepts a single 16 bit keycode, and `ACTION_TAP_DANCE_CONFIG_FN` accepts a void function. The actions will be called in order based on the following:

- single tap
- single hold
- double tap
- single tap and hold
- triple tap
- double tap and hold

For example:

```c
void myFunc(void) {
  SEND_STRING("hello tap dances!");
};

#define TD_MY_DANCE_CUSTOM ACTION_TAP_DANCE_CUSTOM( \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_A), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_B), \
  ACTION_TAP_DANCE_CONFIG_FN(myFunc), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_SECRET_1), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_NO), \
  ACTION_TAP_DANCE_CONFIG_KEY(KC_NO) \
)
```

Next, create the functions we will pass to the QMK tap dance helpers. These will use some utilities that we expose.

```c
void my_td_finished(tap_dance_state_t *state, void *user_data) {
  tap_dance_begin(
    TD_MY_DANCE_CUSTOM, 
    &td_my_dance_state,
    state,
    user_data
  );
}
void my_td_reset(tap_dance_state_t *state, void *user_data) {
  tap_dance_end(
    TD_MY_DANCE_CUSTOM,
    &td_my_dance_state,
    state,
    user_data
  );
}
```

Finally, the last step is to define the global `tap_dance_actions` array.

```c
tap_dance_action_t tap_dance_actions[] = {
  [T_MY_DANCE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, my_td_finished, my_td_reset),
};
```
