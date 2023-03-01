// this config is automatically included when the firmware is built with a gagregrog keymap

#pragma once

#ifdef OLED_ENABLE
  #define OLED_FONT_H "users/gagregrog/oled/gagregrog_font.h"
  #define OLED_SCROLL_TIMEOUT 2000
#endif // OLED_ENABLE

#ifdef KEY_OVERRIDE_ENABLE
  #define USE_BRACKET_OVERRIDE
#endif // KEY_OVERRIDE_ENABLE

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
