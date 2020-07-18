#include "process_unicode.h"
#include "action_util.h"
#include "eeprom.h"

static uint8_t first_flag = 0;

bool process_unicode(uint16_t keycode, keyrecord_t *record) {
  if (keycode > QK_UNICODE && record->event.pressed) {
    if (first_flag == 0) {
      set_unicode_input_mode(eeprom_read_byte(EECONFIG_UNICODEMODE));
      first_flag = 1;
    }
    uint16_t unicode = keycode & 0x7FFF;
    unicode_input_start();
    register_hex(unicode);
    unicode_input_finish();
  }
  return true;
}

