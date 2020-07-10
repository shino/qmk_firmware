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

// En/Ja
#define KC_EN   KC_LANG2    // IME: En
#define KC_JA   KC_LANG1    // IME: Ja

#define KC_LA   KC_F12      // Launcher

// Left thumbs
#define KC_ENex LT(_EXTRA, KC_EN)
#define KC_ENgu LGUI_T(KC_EN)
#define KC_O_ct LCTL_T(KC_O)
#define KC_O_sc MT(MOD_LCTL | MOD_LSFT, KC_O)
#define KC_LAsf LSFT_T(KC_F12)

// Right thumbs
#define KC_C_sf LSFT_T(KC_C)
#define KC_C_ss LT(_S_SYMB, KC_C)
#define KC_SPsy LT(_SYMBOL, KC_SPC)
#define KC_JAal LALT_T(KC_JA)
#define KC_JAex LT(_EXTRA, KC_JA)

// others
#define KC_sENT LSFT(KC_ENT)


// Toggle layers
#define KC__ex   TG(_EXTRA)
#define KC__sy   TG(_SYMBOL)
#define KC__ss   TG(_S_SYMB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_FINCOL] = LAYOUT_kc( \
  //,------+------+------+------+------+------.   ,------+------+------+------+------+------.
      VOLU ,  Q   ,  D   ,  G   ,  Y   , MPLY ,      UP  ,  B   ,  N   ,  P   ,  F   , RGHT ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
      _sy  ,  A   ,  I   ,  U   ,  E   , CAPS ,     BSPC ,  M   ,  S   ,  T   ,  R   , _ex  ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
      VOLD ,  V   ,  Z   ,  W   ,  X   , MNXT ,     DOWN ,  H   ,  J   ,  K   ,  L   , LEFT ,
  //`------+------+------+------+------+------'   `------+------+------+------+------+------'
                    O_sc , LAsf , O_ct , ENgu ,     JAal , SPsy , C_sf , C_ss
  //              `------+------+------+------'   `------+------+------+------'
  ),

  [_SYMBOL] = LAYOUT_kc( \
  //,------+------+------+------+------+------.   ,------+------+------+------+------+------.
           , BSLS ,  7   ,  8   ,  9   ,      ,          , SCLN , LBRC , RBRC , QUOT ,      ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
      _sy  ,  0   ,  4   ,  5   ,  6   ,      ,          , MINS , COMM , DOT  , SLSH ,      ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
           , GRV  ,  1   ,  2   ,  3   ,      ,          , EQL  , LPRN , LPRN , ENT  ,      ,
  //`------+------+------+------+------+------'   `------+------+------+------+------+------'
                         ,      ,      ,      ,          ,      ,      ,
  //              `------+------+------+------'   `------+------+------+------'
  ),

  [_S_SYMB] = LAYOUT_kc( \
  //,------+------+------+------+------+------.   ,------+------+------+------+------+------.
           , PIPE , AMPR , ASTR , LPRN ,      ,          , COLN , LCBR , RCBR , DQUO ,      ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
      _ss  , RPRN , DLR  , PERC , CIRC ,      ,          , UNDS ,  LT  ,  GT  , QUES ,      ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
           , GRV  , EXLM ,  AT  , HASH ,      ,          , PLUS , LPRN , RPRN , sENT ,      ,
  //`------+------+------+------+------+------'   `------+------+------+------+------+------'
                         ,      ,      ,      ,          ,      ,      ,
  //              `------+------+------+------'   `------+------+------+------'
  ),

  [_EXTRA] = LAYOUT_kc( \
  //,------+------+------+------+------+------.   ,------+------+------+------+------+------.
           ,      ,      ,      ,      ,      ,     ESC  , WH_L , WH_D , WH_U , WH_R ,      ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
           ,      ,      ,      ,      ,      ,     BTN1 , MS_L , MS_D , MS_U , MS_R ,      ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
           ,      ,      ,      ,      ,      ,     BTN2 , LEFT , DOWN ,  UP  , RGHT ,      ,
  //`------+------+------+------+------+------'   `------+------+------+------+------+------'
                         ,      ,      ,      ,          , ENT  , BTN1 , BTN2
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
