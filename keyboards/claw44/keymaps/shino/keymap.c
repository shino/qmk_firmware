#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


extern uint8_t is_master;

enum my_layer_number {
    _FINCOL = 0,
    _SYMBOL,
    _EXTRA,
};

enum custom_keycodes {
  FINCOL = SAFE_RANGE,
  SYMBOL,
  EXTRA
};


// Spaces
#define SPsy LT(_SYMBOL, KC_SPC)

// En/Ja
#define EN     KC_LANG2    // IME: En
#define JA     KC_LANG1    // IME: Ja

#define LA     KC_F12      // Launcher

// left thumbs
#define ENex   LT(_EXTRA, EN)
#define ENgu   LGUI_T(EN)
#define O_ct   LCTL_T(KC_O)
#define LAsf   LSFT_T(KC_F12)

// right thumbs
#define C_sf   LSFT_T(KC_C)
#define SPsy   LT(_SYMBOL, KC_SPC)
#define JAal   LALT_T(JA)
#define JAex   LT(_EXTRA, JA)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_FINCOL] = LAYOUT_kc( \
  //,-----+----+-----+-----+-----+-----.   ,-----+-----+-----+-----+-----+-----.
     ESC  , Q  , W   , E   , R   , T   ,     Y   , U   , I   , O   , P   , MINS,
  //|-----+----+-----+-----+-----+-----|   |-----+-----+-----+-----+-----+-----|
     TAB  , A  , S   , D   , F   , G   ,     H   , J   , K   , L   , SCLN, QUOT,
  //|-----+----+-----+-----+-----+-----|   |-----+-----+-----+-----+-----+-----|
     LSFT , Z  , X   , C   , V   , B   ,     N   , M   , COMM, DOT , SLSH, RSFT,
  //`-----+----+-----+-----+-----+-----/   \-----+-----+-----+-----+-----+-----'
                ENex ,ENgu ,O_ct ,LAsf ,    C_sf ,SPsy ,JAal , JAex
  //           `-----+-----+-----+-----'   `-----+-----+-----+-----'
  ),

  //   \ ^ ! & |  @ = + * % -
  // ( # $ " ' ~  ← ↓ ↑ → ` )
  //         { [  ] }

  [_SYMBOL] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     _______, KC_BSLS, KC_CIRC, KC_EXLM, KC_AMPR, KC_PIPE,     KC_AT  , KC_EQL , KC_PLUS, KC_ASTR, KC_PERC, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_LPRN, KC_HASH, KC_DLR , KC_DQT , KC_QUOT, KC_TILD,     KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT, KC_GRV , KC_RPRN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, KC_LCBR, KC_LBRC,     KC_RBRC, KC_RCBR, _______, _______, _______, _______,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       _______, _______, _______, _______,     _______, _______, _______, RESET
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_EXTRA] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,     _______, KC_EQL , KC_PLUS, KC_ASTR, KC_PERC, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,     _______, _______, KC_COMM, KC_DOT , KC_SLSH, _______,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       RESET  , _______, _______, _______,     _______, _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),
};

void matrix_init_user(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
    iota_gfx_init(!has_usb());   // turns on the display
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
  iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case FINCOL:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_FINCOL);
      }
      return false;
      break;
    case SYMBOL:
      if (record->event.pressed) {
        layer_on(_SYMBOL);
      } else {
        layer_off(_SYMBOL);
      }
      return false;
      break;
    case EXTRA:
      if (record->event.pressed) {
        layer_on(_EXTRA);
      } else {
        layer_off(_EXTRA);
      }
      return false;
      break;
  }
  return true;
}
