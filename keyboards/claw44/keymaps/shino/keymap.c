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
    _S_SYMB,
    _EXTRA,
};

enum custom_keycodes {
  FINCOL = SAFE_RANGE,
  SYMBOL,
  S_SYMB,
  EXTRA
};


// common
#define KC_     KC_TRNS

// IME
#define KC_EN   KC_LANG2        // En
#define KC_JA   KC_LANG1        // Ja
#define KC_sf_l LSFT(KC_LEFT)   // Shorten
#define KC_sf_r LSFT(KC_RGHT)   // Widen

// Launcher
#define KC_LA   KC_F2

// Left thumbs
#define KC_LAgu LGUI_T(KC_LA)
#define KC_LAal LALT_T(KC_LA)
#define KC_O_ct LCTL_T(KC_O)

// Right thumbs
#define KC_SPsy LT(_SYMBOL, KC_SPC)
#define KC_Z_ss LT(_S_SYMB, KC_Z)

// with shift
#define KC_A_sf LSFT_T(KC_A)
#define KC_R_sf LSFT_T(KC_R)

// Toggle layers
#define KC__ex   TG(_EXTRA)
#define KC__sy   TG(_SYMBOL)
#define KC__ss   TG(_S_SYMB)


// misc
#define KC_RSET RESET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_FINCOL] = LAYOUT_kc( \
  //,------+------+------+------+------+------.   ,------+------+------+------+------+------.
      VOLU ,  Q   ,  D   ,  G   ,  C   , MPLY ,      UP,    B   ,  N   ,  P   ,  F   , _sy  ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
      VOLD , A_sf ,  I   ,  U   ,  E   , _ex  ,      ENT ,  M   ,  S   ,  T   , R_sf , RGHT ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
      WBAK ,  V   ,  X   ,  W   ,  Y   , MNXT ,     DOWN ,  H   ,  J   ,  K   ,  L   , LEFT ,
  //`------+------+------+------+------+------'   `------+------+------+------+------+------'
                    ESC  , LAal , O_ct ,  EN  ,      JA  , SPsy , Z_ss , BSPC
  //              `------+------+------+------'   `------+------+------+------'
  ),

  [_SYMBOL] = LAYOUT_kc( \
  //,------+------+------+------+------+------.   ,------+------+------+------+------+------.
           , BSLS ,  7   ,  8   ,  9   ,      ,          , DQUO , LBRC , RBRC , ENT  , _sy  ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
           ,  0   ,  4   ,  5   ,  6   ,      ,          , MINS , COMM , DOT  , SLSH ,      ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
           , TILD ,  1   ,  2   ,  3   ,      ,          , EQL  , SCLN , COLN , CAPS ,      ,
  //`------+------+------+------+------+------'   `------+------+------+------+------+------'
                         ,      ,      ,      ,          ,      ,      ,
  //              `------+------+------+------'   `------+------+------+------'
  ),

  [_S_SYMB] = LAYOUT_kc( \
  //,------+------+------+------+------+------.   ,------+------+------+------+------+------.
           , PIPE , AMPR , ASTR , RPRN ,      ,          , QUOT , LCBR , RCBR ,      , RSET ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
           , LPRN , DLR  , PERC , CIRC ,      ,          , UNDS ,  LT  ,  GT  , QUES ,      ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
           , GRV  , EXLM ,  AT  , HASH ,      ,          , PLUS , sf_l , sf_r ,      ,      ,
  //`------+------+------+------+------+------'   `------+------+------+------+------+------'
                         ,      ,      ,      ,          ,      ,      ,
  //              `------+------+------+------'   `------+------+------+------'
  ),

  [_EXTRA] = LAYOUT_kc( \
  //,------+------+------+------+------+------.   ,------+------+------+------+------+------.
           ,      ,      ,      ,      ,      ,          , WH_L , WH_D , WH_U , WH_R ,      ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
           ,      ,      ,      ,      , _ex  ,          , MS_L , MS_D , MS_U , MS_R ,      ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
           ,      ,      ,      ,      ,      ,          , LEFT , DOWN ,  UP  , RGHT ,      ,
  //`------+------+------+------+------+------'   `------+------+------+------+------+------'
                         ,      ,      ,      ,          , BTN1 , BTN2 , ENT
  //              `------+------+------+------'   `------+------+------+------'
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
