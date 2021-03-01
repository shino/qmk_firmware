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

  [_FINCOL] = LAYOUT_kc(
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

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _SYMBOL, _S_SYMB, _EXTRA);
}
