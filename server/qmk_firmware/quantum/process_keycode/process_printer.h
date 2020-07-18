#ifndef PROCESS_PRINTER_H
#define PROCESS_PRINTER_H

#include "quantum.h"

#include "protocol/serial.h"

bool process_printer(uint16_t keycode, keyrecord_t *record);

#endif
