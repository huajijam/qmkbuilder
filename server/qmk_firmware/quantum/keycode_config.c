#include "keycode_config.h"

extern keymap_config_t keymap_config;

uint16_t keycode_config(uint16_t keycode) {

    switch (keycode) {
        case KC_CAPSLOCK:
        case KC_LOCKING_CAPS:
            if (keymap_config.swap_control_capslock || keymap_config.capslock_to_control) {
                return KC_LCTL;
            }
            return keycode;
        case KC_LCTL:
            if (keymap_config.swap_control_capslock) {
                return KC_CAPSLOCK;
            }
            return KC_LCTL;
        case KC_LALT:
            if (keymap_config.swap_lalt_lgui) {
                if (keymap_config.no_gui) {
                    return KC_NO;
                }
                return KC_LGUI;
            }
            return KC_LALT;
        case KC_LGUI:
            if (keymap_config.swap_lalt_lgui) {
                return KC_LALT;
            }
            if (keymap_config.no_gui) {
                return KC_NO;
            }
            return KC_LGUI;
        case KC_RALT:
            if (keymap_config.swap_ralt_rgui) {
                if (keymap_config.no_gui) {
                    return KC_NO;
                }
                return KC_RGUI;
            }
            return KC_RALT;
        case KC_RGUI:
            if (keymap_config.swap_ralt_rgui) {
                return KC_RALT;
            }
            if (keymap_config.no_gui) {
                return KC_NO;
            }
            return KC_RGUI;
        case KC_GRAVE:
            if (keymap_config.swap_grave_esc) {
                return KC_ESC;
            }
            return KC_GRAVE;
        case KC_ESC:
            if (keymap_config.swap_grave_esc) {
                return KC_GRAVE;
            }
            return KC_ESC;
        case KC_BSLASH:
            if (keymap_config.swap_backslash_backspace) {
                return KC_BSPACE;
            }
            return KC_BSLASH;
        case KC_BSPACE:
            if (keymap_config.swap_backslash_backspace) {
                return KC_BSLASH;
            }
            return KC_BSPACE;
        default:
            return keycode;
    }
}

uint8_t mod_config(uint8_t mod) {
    keymap_config.raw = eeconfig_read_keymap();
    if (keymap_config.swap_lalt_lgui) {
        if ((mod & MOD_RGUI) == MOD_LGUI) {
            mod &= ~MOD_LGUI;
            mod |= MOD_LALT;
        } else if ((mod & MOD_RALT) == MOD_LALT) {
            mod &= ~MOD_LALT;
            mod |= MOD_LGUI;
        }
    }
    if (keymap_config.swap_ralt_rgui) {
        if ((mod & MOD_RGUI) == MOD_RGUI) {
            mod &= ~MOD_RGUI;
            mod |= MOD_RALT;
        } else if ((mod & MOD_RALT) == MOD_RALT) {
            mod &= ~MOD_RALT;
            mod |= MOD_RGUI;
        }
    }
    if (keymap_config.no_gui) {
        mod &= ~MOD_LGUI;
        mod &= ~MOD_RGUI;
    }

    return mod;
}