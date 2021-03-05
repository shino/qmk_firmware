/* Copyright 2020 Yoichiro Tanaka
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layer_number {
    _FINCOL = 0,
    _SYMBOL,
    _S_SYMB,
    _EXTRA,
};

enum custom_keycodes {
  FINCOL = SAFE_RANGE,
  SYMBOL_ON,
  SYMBOL_OFF,
  S_SYMB,
  EXTRA_ON,
  EXTRA_OFF
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
#define KC_ex   EXTRA_ON
#define KC_exx  EXTRA_OFF
#define KC_sy   SYMBOL_ON
#define KC_syx  SYMBOL_OFF
#define KC__ss   TG(_S_SYMB)


// misc
#define KC_RSET RESET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_FINCOL] = LAYOUT_kc(
  //,------+------+------+------+------+------.   ,------+------+------+------+------+------.
      VOLU ,  Q   ,  D   ,  G   ,  C   , MPLY ,      UP,    B   ,  N   ,  P   ,  F   ,  sy  ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
      VOLD , A_sf ,  I   ,  U   ,  E   ,  ex  ,      ENT ,  M   ,  S   ,  T   , R_sf , RGHT ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
      WBAK ,  V   ,  X   ,  W   ,  Y   , MNXT ,     DOWN ,  H   ,  J   ,  K   ,  L   , LEFT ,
  //`------+------+------+------+------+------'   `------+------+------+------+------+------'
                    ESC  ,  EN  , O_ct , LAal ,     Z_ss , SPsy ,  JA  , BSPC
  //              `------+------+------+------'   `------+------+------+------'
  ),

  [_SYMBOL] = LAYOUT_kc( \
  //,------+------+------+------+------+------.   ,------+------+------+------+------+------.
           , BSLS ,  7   ,  8   ,  9   ,      ,          , DQUO , LBRC , RBRC , ENT  , syx  ,
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
           ,      ,      ,      ,      , exx  ,          , MS_L , MS_D , MS_U , MS_R ,      ,
  //|------+------+------+------+------+------|   |------+------+------+------+------+------|
           ,      ,      ,      ,      ,      ,          , LEFT , DOWN ,  UP  , RGHT ,      ,
  //`------+------+------+------+------+------'   `------+------+------+------+------+------'
                         ,      ,      ,      ,          , BTN1 , BTN2 ,
  //              `------+------+------+------'   `------+------+------+------'
  ),
};


/* #ifdef RGBLIGHT_ENABLE */
/* const rgblight_segment_t PROGMEM my_fincol_layer[] = RGBLIGHT_LAYER_SEGMENTS( */
/*     {0, 12, 0,0,0} */
/* ); */
/* const rgblight_segment_t PROGMEM my_sy_layer[] = RGBLIGHT_LAYER_SEGMENTS( */
/*     {0, 12, HSV_PURPLE} */
/* ); */
/* const rgblight_segment_t PROGMEM my_ex_layer[] = RGBLIGHT_LAYER_SEGMENTS( */
/*     {0, 12, HSV_RED} */
/* ); */

/* const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST( */
/*     my_fincol_layer, */
/*     my_sy_layer, */
/*     my_ex_layer */
/* ); */
/* #endif */

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_sethsv_noeeprom(0, 0, 0);
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case SYMBOL_ON:
    if (record->event.pressed) {
      layer_on(_SYMBOL);
#ifdef RGBLIGHT_ENABLE
      rgblight_setrgb(0x00,  0x00, 0xFF);
#endif
    }
    return false;
  case SYMBOL_OFF:
    if (record->event.pressed) {
      layer_off(_SYMBOL);
#ifdef RGBLIGHT_ENABLE
      rgblight_setrgb(0x00,  0x00, 0x00);
#endif
    }
    return false;
  case EXTRA_ON:
    if (record->event.pressed) {
      layer_on(_EXTRA);
#ifdef RGBLIGHT_ENABLE
      rgblight_setrgb(0x00,  0xFF, 0x00);
#endif
    }
    return false;
  case EXTRA_OFF:
    if (record->event.pressed) {
      layer_off(_EXTRA);
#ifdef RGBLIGHT_ENABLE
      rgblight_setrgb(0x00,  0x00, 0x00);
#endif
    }
    return false;
  }
  return true;
}
