# Secrets

Provide a list of 5 secret strings that can be mapped to keycodes and used in tapdances.

## Setup

Add to your `rules.mk`:

```make
INCLUDE_SECRETS = yes
```

Create a file `users/gagregrog/secrets/secrets.h` which consists of:

```c
static const char * secrets[] = {
  "real_secret_1",
  "real_secret_2",
  "real_secret_3",
  "real_secret_4",
  "real_secret_5"
};
```

You can disable secrets at compile time by passing `-e NO_SECRETS=yes`. For example:

```bash
qmk flash handwired/twokey -e NO_SECRETS=yes
```

## How it works

It will expose 5 custom keycodes, `KC_SECRET_1` through `KC_SECRET_5`. You can use these as normal keycodes which will be handled by `process_record_user` automatically in the `gagregrog` userspace. It will also expose a `send_secret` function which you can use like `send_secret(KC_SECRET_1)`.

## Credits

Based off of [Drashna's work](/users/drashna/keyrecords/secrets.md).
