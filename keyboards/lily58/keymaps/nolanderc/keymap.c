#include QMK_KEYBOARD_H

enum custom_keycodes {
    // Swedish symbols Ö, Ä and Å.
    KC_ODOTS = SAFE_RANGE,
    KC_ADOTS,
    KC_ARING,
};

enum layer_number {
    _DVORAK = 0,
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DVORAK] = LAYOUT(
            KC_LGUI,  KC_1,      KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
            KC_TAB,   KC_QUOT,   KC_COMM, KC_DOT,  KC_P,    KC_Y,                     KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
            KC_ESC,   KC_A,      KC_O,    KC_E,    KC_U,    KC_I,                     KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
            KC_LCTL,  KC_SCLN,   KC_Q,    KC_J,    KC_K,    KC_X, QK_REBOOT,QK_REBOOT,KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_BSLS,
                               KC_LGUI, KC_LALT, KC_LSFT,  MO(_LOWER),        KC_ENTER, KC_SPC, MO(_RAISE), KC_RALT
            ),

    [_QWERTY] = LAYOUT(
            _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______,  _______,
            _______,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     _______,
            _______,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  _______,
            _______,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, _______,  _______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  _______,
                                _______, _______, _______,  _______,           _______, _______, _______, _______
            ),

    [_LOWER] = LAYOUT(
        TG(_QWERTY), _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______,   KC_DELETE,
            _______, KC_GRV,  KC_LT,   KC_GT,   KC_PIPE, KC_CIRC,                      KC_PIPE, KC_AMPR, KC_LBRC, KC_RBRC, KC_PERC,   KC_TILD,
            _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_ASTR, KC_EQUAL,KC_LPRN, KC_RPRN, S(KC_S),   S(KC_MINS),
            _______, KC_COLON,KC_2,    KC_1,    KC_0,    KC_CIRC, _______,    _______, KC_HASH, KC_PLUS, KC_LCBR, KC_RCBR, KC_DOLLAR, KC_CIRC,
                                 _______, _______, _______, _______,               KC_BSPC,  _______, _______, _______
            ),

    [_RAISE] = LAYOUT(
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_PRINT_SCREEN,
            _______, KC_ARING,KC_PGDN, KC_UP,   KC_PGUP, KC_F11,                      KC_F12,  _______, _______, _______, _______, _______,
            _______, KC_ADOTS,KC_LEFT, KC_DOWN, KC_RGHT, S(C(KC_TAB)),              C(KC_TAB), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
            _______, KC_ODOTS,KC_ODOTS,KC_DOWN, KC_UP,   _______,  _______, _______,  _______, _______, _______, _______, _______, _______,
                                _______, _______, _______,  _______,            _______,  _______, _______, _______
            ),

    [_ADJUST] = LAYOUT(
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_REBOOT,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                _______, _______, _______,  _______,            _______,  _______, _______, _______
            )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master())
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

const char* get_host_os_name(void) {
    switch (detected_host_os()) {
        case OS_LINUX: return "Linux";
        case OS_WINDOWS: return "Windows";
        case OS_MACOS: return "MacOS";
        case OS_IOS: return "iOS";
        case OS_UNSURE:
        default:
            return "?";
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // If you want to change the display of OLED, you need to change here
        oled_write_ln(read_layer_state(), false);
        oled_write("OS: ", false); oled_write_ln(get_host_os_name(), false);
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
        //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
        //oled_write_ln(read_host_led_state(), false);
        //oled_write_ln(read_timelog(), false);
    } else {
        oled_write(read_logo(), false);
    }
    return false;
}
#endif // OLED_ENABLE

void send_key(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        register_code16(keycode);
    } else {
        unregister_code16(keycode);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_ENABLE
        set_keylog(keycode, record);
#endif
    }

    switch (keycode) {
        // Assumes a `se(us)` layout in XKB which maps AltGr + <key> to the
        // corresponding symbol on a Swedish ISO keyboard.
        // On Windows, the keys seem to be different in the US International layout, so
        // will need fixing.
        case KC_ODOTS: send_key(ALGR(KC_SCLN), record); return false;
        case KC_ADOTS: send_key(ALGR(KC_QUOT), record); return false;
        case KC_ARING: send_key(ALGR(KC_LBRC), record); return false;

        default: return true;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_KB_VOLUME_UP);
    } else {
        tap_code(KC_KB_VOLUME_DOWN);
    }
    return true;
}

