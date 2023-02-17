# MCU name
MCU = atmega32u4

# use for right half (with trackpoint)
# Bootloader selection
# elite-c
BOOTLOADER = atmel-dfu

# use for left half (without trackpoint)
# Bootloader selection
# Pro Micro
# BOOTLOADER = caterina

PS2_MOUSE_ENABLE = yes
PS2_ENABLE = yes
PS2_DRIVER = usart

# https://getreuer.info/posts/keyboards/mouse-turbo-click/index.html
SRC += features/mouse_turbo_click.c

DEFERRED_EXEC_ENABLE = yes


COMMAND_ENABLE = no
RGBLIGHT_ENABLE = yes
AUTO_SHIFT_ENABLE = no
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
LTO_ENABLE = yes
