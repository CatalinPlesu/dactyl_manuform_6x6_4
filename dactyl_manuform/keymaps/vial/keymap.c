#include QMK_KEYBOARD_H

#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{5, 7}, {4, 7}, {3, 7}, {2, 7}, {1, 7}, {0, 7}},
  {{5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 8}},
  {{5, 9}, {4, 9}, {3, 9}, {2, 9}, {1, 9}, {0, 9}},
  {{5, 10}, {4, 10}, {3, 10}, {2, 10}, {1, 10}, {0, 10}},
  {{5, 11}, {4, 11}, {3, 11}, {2, 11}, {1, 11}, {0, 11}},
  {{5, 12}, {4, 12}, {3, 12}, {2, 12}, {1, 12}, {0, 12}},
  {{5, 13}, {4, 13}, {3, 13}, {2, 13}, {1, 13}, {0, 13}},
  {{5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
  {{5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
  {{5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
  {{5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
  {{5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}},
  {{5, 5}, {4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 5}},
  {{5, 6}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}},
};

enum custom_keycodes {
    U_SH_TG = QK_KB_0, 
    U_CW_TOGG,
    U_QK_LOCK,
};

#define RECORED_USER_FUNCTION(kEYCODE, FUNCTION)\
        case kEYCODE:\
            if (record->event.pressed) {\
                FUNCTION;\
            }\
            return false

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
        const bool is_combo = record->event.type == COMBO_EVENT;
        uprintf("0x%04X,%u,%u,%u,%d,0x%02X,0x%02X,%u\n",
             keycode,
             is_combo ? 254 : record->event.key.row,
             is_combo ? 254 : record->event.key.col,
             get_highest_layer(layer_state),
             record->event.pressed,
             get_mods(),
             get_oneshot_mods(),
             record->tap.count
             );
    #endif
    switch (keycode) {
        RECORED_USER_FUNCTION(U_SH_TG, swap_hands_toggle());
        RECORED_USER_FUNCTION(U_CW_TOGG, caps_word_toggle());
        RECORED_USER_FUNCTION(U_QK_LOCK, process_key_lock(&keycode,record));

        default:
            return true;
    }
}



enum custom_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
};


#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_F1  , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 ,                         KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,KC_F12 ,
        KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
        KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
        KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
        KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLS,
        _______,_______, KC_LBRC,KC_RBRC,                                                       KC_PLUS, KC_EQL,_______,_______,
                                         RAISE,KC_SPC,                        KC_ENT, LOWER,
                                         KC_LSFT,KC_BSPC,                         KC_DEL,  KC_RSFT,
                                         KC_LCTL, KC_LGUI,                        KC_LALT, KC_RCTL
    ),

    [_LOWER] = LAYOUT(
        KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6  ,                         KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,KC_F12 ,
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
        _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,_______,KC_PLUS,
        _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,
        _______,_______,_______,_______,_______,_______,                        _______, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,U_SH_TG,
                                _______,_______,_______,KC_PSCR,            _______, KC_P0,_______,_______,
                                                _______,_______,            _______,_______,
                                                _______,_______,            _______,_______,
                                                _______,_______,            _______,_______
    ),

    [_RAISE] = LAYOUT(
        KC_F12 , KC_F1, KC_F2 , KC_F3, KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
        KC_GRV,DM_REC1,DM_RSTP,DM_PLY1,_______,KC_LBRC,                        KC_RBRC,_______,KC_NUM ,KC_INS ,KC_SCRL,KC_MUTE,
        _______,KC_LEFT,KC_DOWN  ,KC_UP,KC_RGHT,KC_LPRN,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU,
        U_CW_TOGG,_______,KC_MS_BTN2,KC_MS_BTN3,KC_MS_BTN1,KC_MS_WH_UP,                        KC_MS_LEFT,KC_MS_DOWN,KC_MS_UP,KC_MS_RIGHT,_______,KC_VOLD,
        U_SH_TG,_______,_______,KC_MS_WH_LEFT,KC_MS_WH_RIGHT,KC_MS_WH_DOWN,                        _______,_______,_______,_______,_______,_______,
                                _______,_______,_______,_______,            KC_EQL ,_______,_______,_______,
                                                _______,_______,            _______,_______,
                                               _______,_______,            _______,_______,
                                               _______,_______,            _______,_______
    ),

};