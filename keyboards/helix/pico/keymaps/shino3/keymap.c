#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum layer_number {
    _FINCOL = 0,
    _SYMBOL,
    _S_SYMB,
    _EXTRA
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
  //,------+------+------+------+------+------.               ,------+------+------+------+------+------.
       Q   ,  D   ,  G   ,  C   , MPLY , VOLU ,                 _sy  ,  UP  ,  B   ,  N   ,  P   ,  F   ,
  //|------+------+------+------+------+------|               |------+------+------+------+------+------|
      A_sf ,  I   ,  U   ,  E   , _ex  , VOLD ,                 RGHT ,  ENT ,  M   ,  S   ,  T   , R_sf ,
  //|------+------+------+------+------+------|               |------+------+------+------+------+------|
       V   ,  X   ,  W   ,  Y   , MNXT ,      ,                 LEFT , DOWN ,  H   ,  J   ,  K   ,  L   ,
  //|------+------+------+------+------+------+------' `------+------+------+------+------+------+------'
      WBAK ,      ,      , ESC  , LAal , O_ct ,  EN  ,    JA  , SPsy , Z_ss , BSPC ,      ,      ,
  //`------+------+------+------+------+------+------' `------+------+------+------+------+------+------'
  ),

  [_SYMBOL] = LAYOUT_kc( \
  //,------+------+------+------+------+------.               ,------+------+------+------+------+------.
      BSLS ,  7   ,  8   ,  9   ,      ,      ,                 _sy  ,      , DQUO , LBRC , RBRC , ENT  ,
  //|------+------+------+------+------+------|               |------+------+------+------+------+------|
       0   ,  4   ,  5   ,  6   ,      ,      ,                      ,      , MINS , COMM , DOT  , SLSH ,
  //|------+------+------+------+------+------|               |------+------+------+------+------+------|
      TILD ,  1   ,  2   ,  3   ,      ,      ,                      ,      , EQL  , SCLN , COLN , CAPS ,
  //|------+------+------+------+------+------+------' `------+------+------+------+------+------+------'
           ,      ,      ,      ,      ,      ,      ,        ,      ,      ,      ,      ,      ,
  //`------+------+------+------+------+------+------' `------+------+------+------+------+------+------'
  ),

  [_S_SYMB] = LAYOUT_kc( \
  //,------+------+------+------+------+------.               ,------+------+------+------+------+------.
      PIPE , AMPR , ASTR , RPRN ,      ,      ,                 RSET ,      , QUOT , LCBR , RCBR ,      ,
  //|------+------+------+------+------+------|               |------+------+------+------+------+------|
      LPRN , DLR  , PERC , CIRC ,      ,      ,                      ,      , UNDS ,  LT  ,  GT  , QUES ,
  //|------+------+------+------+------+------|               |------+------+------+------+------+------|
      GRV  , EXLM ,  AT  , HASH ,      ,      ,                      ,      , PLUS , sf_l , sf_r ,      ,
  //|------+------+------+------+------+------+------' `------+------+------+------+------+------+------'
           ,      ,      ,      ,      ,      ,      ,        ,      ,      ,      ,      ,      ,
  //`------+------+------+------+------+------+------' `------+------+------+------+------+------+------'
  ),

  [_EXTRA] = LAYOUT_kc( \
  //,------+------+------+------+------+------.               ,------+------+------+------+------+------.
           ,      ,      ,      ,      ,      ,                      ,      , WH_L , WH_D , WH_U , WH_R ,
  //|------+------+------+------+------+------|               |------+------+------+------+------+------|
           ,      ,      ,      , _ex  ,      ,                      ,      , MS_L , MS_D , MS_U , MS_R ,
  //|------+------+------+------+------+------|               |------+------+------+------+------+------|
           ,      ,      ,      ,      ,      ,                      ,      , LEFT , DOWN ,  UP  , RGHT ,
  //|------+------+------+------+------+------+------' `------+------+------+------+------+------+------'
           ,      ,      ,      ,      ,      ,      ,        , BTN1 , BTN2 , ENT  ,      ,      ,
  //`------+------+------+------+------+------+------' `------+------+------+------+------+------+------'
  )

};


// define variables for reactive RGB
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FINCOL:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_FINCOL);
      }
      return false;
      break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_SYMBOL  (1<<_SYMBOL)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_SYMBOL:
           matrix_write_P(matrix, PSTR("Symbol"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
