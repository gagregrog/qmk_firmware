#include "gagregrog.h"

#ifdef OLED_SHOW_DOGS
void render_dogs(void) {
     // dogs uncompressed
     // static const char PROGMEM dogs[] = {
     //      0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54,
     //      0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74,
     //      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
     //      0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
     //      0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
     // };

    // dogs compressed
     static const char PROGMEM dogs[] = {
          0xFF, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA0, 0xA1, 0xFF, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xFF,
          0xFF, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0xFF, 0xFF, 0xFF, 0xFF, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xFF,
          0xFF, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0xFF, 0xFF, 0xFF, 0xFF, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xFF, 0xFF,
          0xFF, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xFF, 0xFF,
          0xFF, 0xFF, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBC, 0xBD, 0xFF, 0xBE, 0xFF, 0xFF, 0xFF,
          0x00
     };

     oled_set_cursor(0, 1);
     oled_write_P(dogs, false);
}
#endif // OLED_SHOW_DOGS

void render_layer_text(void) {
  oled_write_P(PSTR(" "), false);

  switch (get_highest_layer(layer_state)) {
    case _LAYER_COLEMAK_DH:
      oled_write_ln_P(PSTR("\n  Layer: Colemak DH  "), false);
      break;
    case _LAYER_QWERTY:
      oled_write_ln_P(PSTR("\n    Layer: QWERTY    "), false);
      break;
    case _LAYER_NUM:
      oled_write_ln_P(PSTR("\n   Layer: Numeric    "), false);
      break;
    case _LAYER_UTIL:
      oled_write_ln_P(PSTR("\n   Layer: Utility    "), false);
      break;
    case _LAYER_SETTINGS:
      oled_write_ln_P(PSTR("\n   Layer: Settings   "), false);
      break;
    default:
      oled_write_ln_P(PSTR("\n   Layer: Undefined  "), false);
  }
}

#ifdef OLED_FLIP_180
__attribute__ ((weak))
oled_rotation_t oled_init_keymap(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return oled_init_keymap(rotation);
}
#endif // OLED_FLIP_180

__attribute__ ((weak))
bool oled_task_keymap(void) {
  return false;
}

bool oled_task_user(void) {
#ifdef OLED_SHOW_DOGS
  render_dogs();
#endif
  render_layer_text();

  return oled_task_keymap();
}
