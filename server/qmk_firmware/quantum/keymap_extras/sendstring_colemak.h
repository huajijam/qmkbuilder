/* Sendstring definitions for the Colemak layout */
#ifndef SENDSTRING_COLEMAK
#define SENDSTRING_COLEMAK

#include "keymap_colemak.h"

const uint8_t ascii_to_keycode_lut[0x80] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    KC_BSPC, KC_TAB, KC_ENT, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, KC_ESC, 0, 0, 0, 0,
    KC_SPC, KC_1, KC_QUOT, KC_3, KC_4, KC_5, KC_7, KC_QUOT,
    KC_9, KC_0, KC_8, KC_EQL, KC_COMM, KC_MINS, KC_DOT, KC_SLSH,
    KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,
    KC_8, KC_9, CM_SCLN, CM_SCLN, KC_COMM, KC_EQL, KC_DOT, KC_SLSH,
    KC_2, CM_A, CM_B, CM_C, CM_D, CM_E, CM_F, CM_G,
    CM_H, CM_I, CM_J, CM_K, CM_L, CM_M, CM_N, CM_O,
    CM_P, CM_Q, CM_R, CM_S, CM_T, CM_U, CM_V, CM_W,
    CM_X, CM_Y, CM_Z, KC_LBRC, KC_BSLS, KC_RBRC, KC_6, KC_MINS,
    KC_GRV, CM_A, CM_B, CM_C, CM_D, CM_E, CM_F, CM_G,
    CM_H, CM_I, CM_J, CM_K, CM_L, CM_M, CM_N, CM_O,
    CM_P, CM_Q, CM_R, CM_S, CM_T, CM_U, CM_V, CM_W,
    CM_X, CM_Y, CM_Z, KC_LBRC, KC_BSLS, KC_RBRC, KC_GRV, KC_DEL
};

#endif
