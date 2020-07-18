/* Sendstring definitions for the Dvorak layout */
#ifndef SENDSTRING_DVORAK
#define SENDSTRING_DVORAK

#include "keymap_dvorak.h"

const uint8_t ascii_to_keycode_lut[0x80] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    KC_BSPC, KC_TAB, KC_ENT, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, KC_ESC, 0, 0, 0, 0,
    KC_SPC, DV_1, DV_QUOT, DV_3, DV_4, DV_5, DV_7, DV_QUOT,
    DV_9, DV_0, DV_8, DV_EQL, DV_COMM, DV_MINS, DV_DOT, DV_SLSH,
    DV_0, DV_1, DV_2, DV_3, DV_4, DV_5, DV_6, DV_7,
    DV_8, DV_9, DV_SCLN, DV_SCLN, DV_COMM, DV_EQL, DV_DOT, DV_SLSH,
    DV_2, DV_A, DV_B, DV_C, DV_D, DV_E, DV_F, DV_G,
    DV_H, DV_I, DV_J, DV_K, DV_L, DV_M, DV_N, DV_O,
    DV_P, DV_Q, DV_R, DV_S, DV_T, DV_U, DV_V, DV_W,
    DV_X, DV_Y, DV_Z, DV_LBRC, DV_BSLS, DV_RBRC, DV_6, DV_MINS,
    DV_GRV, DV_A, DV_B, DV_C, DV_D, DV_E, DV_F, DV_G,
    DV_H, DV_I, DV_J, DV_K, DV_L, DV_M, DV_N, DV_O,
    DV_P, DV_Q, DV_R, DV_S, DV_T, DV_U, DV_V, DV_W,
    DV_X, DV_Y, DV_Z, DV_LBRC, DV_BSLS, DV_RBRC, DV_GRV, KC_DEL
};

#endif
