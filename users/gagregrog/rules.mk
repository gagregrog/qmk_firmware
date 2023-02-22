# these rules are automatically included when the firmware is built with a gagregrog keymap

SRC += gagregrog.c

ifeq ($(strip $(POINTING_DEVICE_INVERT_SCROLL)), yes)
    OPT_DEFS += -DPOINTING_DEVICE_INVERT_SCROLL
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += $(USER_PATH)/oled/oled_util.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += $(USER_PATH)/led/led_util.c
endif

ifeq ($(strip $(MOUSE_TURBO_CLICK)), yes)
    OPT_DEFS += -DMOUSE_TURBO_CLICK
    # https://getreuer.info/posts/keyboards/mouse-turbo-click/index.html
    SRC += $(USER_PATH)/mouse_turbo_click/mouse_turbo_click.c
    ifneq ($(strip $(DEFERRED_EXEC_ENABLE)), yes)
        DEFERRED_EXEC_ENABLE = yes
    endif
    ifneq ($(strip $(MOUSEKEY_ENABLE)), yes)
        MOUSEKEY_ENABLE = yes
    endif
endif
