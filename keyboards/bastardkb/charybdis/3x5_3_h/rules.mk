# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
AUDIO_SUPPORTED = no        # Audio is not supported

RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
RGBLIGHT_SUPPORTED = no    # RGB underglow is supported, but not enabled by default

RGB_MATRIX_SUPPORTED = yes  # RGB matrix is supported and enabled by default
RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix functionality
RGB_MATRIX_DRIVER = ws2812

SERIAL_DRIVER = vendor
WS2812_DRIVER = vendor

SPLIT_KEYBOARD = yes

POINTING_DEVICE_ENABLE = yes # Enable trackball
POINTING_DEVICE_DRIVER = pmw3389

MOUSE_SHARED_EP = yes # Unify multiple HID interfaces into a single Endpoint
# KEYBOARD_SHARED_EP = yes

# EEPROM_DRIVER = spi

# DEBOUNCE_TYPE = asym_eager_defer_pk

PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS.

USE_DEFAULT_TD_ACTIONS = yes
KEY_OVERRIDE_ENABLE = yes 
