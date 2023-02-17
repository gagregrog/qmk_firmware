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
