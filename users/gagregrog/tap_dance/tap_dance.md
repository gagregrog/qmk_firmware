# Tap Dance

When Tap Dances are enabled, these utilities will be exposed automatically.  Currently, these utils allow you to define key taps/holds for `KC_` keycodes, `KC_SECRET_`S, and user-defined functions.

## Configuration

In your `keymap.c`, create an enum to hold all of your tap dances. Then, for convenience, create defines for the new keycodes to use in your layout.

```c
enum tap_dance_keys {
  T_MY_DANCE,
};

#define TD_MY_DANCE     TD(T_MY_DANCE)
```

For each tap dance you will need to create a state container that looks like this:

```c
static td_tap_t td_my_dance_state = TD_INIT_STATE;
```

Next, create an array to hold your tap dance actions. Each odd index will correspond to a tap action, and each even index will correspond to a hold action. Hold actions for regular `KC_` keycodes will remain held until released, and as such will continue to register with the host system. Taps, on the other hand, will only be sent once and cannot be held. The array must not be sparse, but there is a helper if you want to skip items. Use the helper macros to define your functinoality.

For example:

```c
static void myFunc(void) {
  SEND_STRING("hello tap dances!");
};

static td_action_config my_actions[] = {
  ACTION_TAP_DANCE_CONFIG_KEY(KC_1), // send 1 when tapped once
  ACTION_TAP_DANCE_CONFIG_FN(myFunc), // call the function myFunc when held
  ACTION_TAP_DANCE_CONFIG_NULL, // do nothing when double tapped
  ACTION_TAP_DANCE_CONFIG_KEY(KC_SECRET_1), // send secret 1 when tapped once and then held
  ACTION_TAP_DANCE_CONFIG_BOOT // put the keyboard into bootloader mode so you can flash new code to it when tapped 3 times
};
```

Next, create the functions we will pass to the QMK tap dance macros. These will use some utilities that we expose.

```c
void my_td_begin(tap_dance_state_t *state, void *user_data) {
  tap_dance_begin(
    my_actions,
    5, // number of items in actions array
    &td_my_dance_state,
    state
  );
}
void my_td_reset(tap_dance_state_t *state, void *user_data) {
  tap_dance_end(
    my_actions,
    5,
    &td_my_dance_state,
    states
  );
}
```

Finally, the last step is to define the global `tap_dance_actions` array.

```c
tap_dance_action_t tap_dance_actions[] = {
  [T_MY_DANCE]  = ACTION_TAP_DANCE_WRAPPER(my_td_begin, my_td_end),
  // add as many tapdance configs as you want
};
```
