#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _EUCALX = 0,
    _QWERTY,
    _CURNUM,
    _SYMBOL,
    _SHOTL,
    _SHOTR,
    _MOUSE,
    _ADJUST
};

enum custom_keycodes {
  EUCALX = SAFE_RANGE,
  QWERTY,
  CURNUM,
  SYMBOL,
  SHOTL,
  SHOTR,
  MOUSE,
  ADJUST,
  BACKLIT,
  EISU,
  KANA,
  RGBRST
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


// EUCALX : Home position keys

#define A_LS LSFT_T(KC_A)
#define O_SY LT(_SYMBOL, KC_O)
#define E_CN LT(_CURNUM, KC_E)
#define I_SL LT(_SHOTL, KC_I)

#define N_SR LT(_SHOTR, KC_N)
#define M_CN LT(_CURNUM, KC_M)
#define S_SY LT(_SYMBOL, KC_S)
#define T_RS RSFT_T(KC_T)
#define SLSH_RS SFT_T(KC_SLSH)
#define J_RS RSFT_T(KC_J)

#define H_SR LT(_SHOTR, KC_H)
#define J_CN LT(_CURNUM, KC_J)
#define K_SY LT(_SYMBOL, KC_K)
#define L_RS RSFT_T(KC_L)

// EUCALX: other keys
// TODO(shino): Want to input UNDS without shift, and input MINS with shift


// Home position keys for QWERTY

// #define A_LS LSFT_T(KC_A)
#define S_SY LT(_SYMBOL, KC_S)
#define D_CN LT(_CURNUM, KC_D)
#define F_SL LT(_SHOTL, KC_F)
// #define Z_LS LSFT_T(KC_Z)

#define J_SR LT(_SHOTR, KC_J)
#define K_CN LT(_CURNUM, KC_K)
#define L_SY LT(_SYMBOL, KC_L)
// This does not work 2019-01-03, mod-tap MT is only for basic keys
// #define UNDS_RS SFT_T(KC_UNDS)
#define MINS_RS RSFT_T(KC_MINS)
#define SLSH_RS SFT_T(KC_SLSH)
#define J_RS RSFT_T(KC_J)

#define H_SR LT(_SHOTR, KC_H)
#define J_CN LT(_CURNUM, KC_J)
#define K_SY LT(_SYMBOL, KC_K)
#define L_RS RSFT_T(KC_L)

// Spaces
#define SP_LCTL LCTL_T(KC_SPC)
#define SP_RCTL RCTL_T(KC_SPC)
#define SP_RALT RALT_T(KC_SPC)

// shots: macOS
#define GUI_ENT  LGUI(KC_ENT)
#define G_C_S_4  LGUI(LCTL(LSFT(KC_4))) // Screen capture
#define EN       LCTL(LSFT(KC_SCLN))    // IME: En
#define JA       LCTL(LSFT(KC_J))       // IME: Ja
#define SH_LEFT  LSFT(KC_LEFT)          // IME
#define SH_RGHT  LSFT(KC_RGHT)          // IME
#define C_TAB    LCTL(KC_TAB)           // App Switch
#define C_S_TAB  LCTL(LSFT(KC_TAB))     // App Switch
#define C_3      LCTL(KC_3)             // QuickSilver
#define C_RBRC   LCTL(KC_RBRC)          // QuickSilver


// shots: Slack
#define GUI_K    LGUI(KC_K)             // Jump
#define GUI_1    LGUI(KC_1)             // Workspace 1
#define GUI_2    LGUI(KC_2)
#define GUI_3    LGUI(KC_3)
#define GUI_4    LGUI(KC_4)
#define GUI_5    LGUI(KC_5)
#define G_S_ENT  LGUI(LSFT(KC_ENT))     // Create snippet

// shots: Emacs
#define C_SPC    LCTL(KC_SPC)
#define C_C      LCTL(KC_C)
#define C_G      LCTL(KC_G)
#define C_H      LCTL(KC_H)
#define C_M      LCTL(KC_M)
#define C_Z      LCTL(KC_Z)

#define C_COMM   LCTL(KC_COMM)
#define C_DOT    LCTL(KC_DOT)
#define C_SLSH   LCTL(KC_SLSH)
#define C_SCLN   LCTL(KC_SCLN)
#define M_X      RALT(KC_X)
#define M_RET    RALT(KC_ENT)

// shots: GNU Screen
#define C_LBRC   LCTL(KC_LBRC)

// Toggle layers
#define MOUSE_T TG(_MOUSE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* EucalynX
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |  X   |  W   |  Y   |  F   |  Q   |             |  /   |  J   |  K   |  R   |   P  |  Up  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  | A/Sh | O/Sy | E/CN | I/SL |  L   |             |  B   | N/SR | M/Ra | S/Lo | T/Sh | Down |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|  Z   |  C   |  V   |  U   | . >  |             | , <  |  G   |  D   |  H   | _ -  |Enter |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |Adjust| LCtl | Left |Right | LGui |Spc/Ct|Space |Space |Spc/Al| RAlt | Next | Play | Vol- | Vol+ |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_EUCALX] = LAYOUT( \
      KC_ESC,  KC_X,    KC_W,    KC_Y,    KC_F,    KC_Q,                    KC_SLSH, KC_J,    KC_K,    KC_R,    KC_P,    KC_UP, \
      KC_TAB,  A_LS,    O_SY,    E_CN,    I_SL,    KC_L,                    KC_B,    N_SR,    M_CN,    S_SY,    T_RS,    KC_DOWN, \
      KC_LSFT, KC_Z,    KC_C,    KC_V,    KC_U,    KC_DOT,                  KC_COMM, KC_G,    KC_D,    KC_H,    KC_MINS, KC_ENT , \
      ADJUST,  MOUSE_T, KC_LEFT, KC_RGHT, KC_LGUI, SP_LCTL, KC_SPC, KC_SPC, SP_RALT, KC_RALT, KC_MNXT, KC_MPLY, KC_VOLD, KC_VOLU \
      ),

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  Up  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  | A/Sh | S/Sy | D/CN | F/SL |   G  |             |   H  | J/SR | K/CN | L/Sy | -/Sh | Down |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift| Z/Sh |   X  |   C  |   V  | , <  |             |   B  |   N  |   M  | . >  |/?/Sh |Enter |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |Adjust| LCtl | Left |Right | LGui |Spc/Ct|Space |Space |Spc/Al| RAlt | Next | Play | Vol- | Vol+ |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_UP, \
      KC_TAB,  A_LS,    S_SY,    D_CN,    F_SL,    KC_G,                    KC_H,    J_SR,    K_CN,    L_SY,    MINS_RS, KC_DOWN, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_COMM,                 KC_B,    KC_N,    KC_M,    KC_DOT,  KC_SLSH, KC_ENT , \
      ADJUST,  MOUSE_T, KC_LEFT, KC_RGHT, KC_LGUI, SP_LCTL, KC_SPC, KC_SPC, SP_RALT, KC_RALT, KC_MNXT, KC_MPLY, KC_VOLD, KC_VOLU \
      ),

  /* CurNum
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |  7   |  8   |  9   |      |             |  !   |  @   |  #   |  $   |  %   | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  0   |  1   |  2   |  3   |      |             | ---- |  -   |   =  |  "   |  '   |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |  4   |  5   |  6   |      |             |  ^   |  &   |  *   |  +   |  ?   |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Prev |      | Mute |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_CURNUM] = LAYOUT( \
      _______, _______, KC_7,    KC_8,    KC_9,    _______,                   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, \
      _______, KC_0,    KC_1,    KC_2,    KC_3,    _______,                   _______, KC_MINS, KC_EQL,  KC_DQUO, KC_QUOT, _______, \
      _______, _______, KC_4,    KC_5,    KC_6,    _______,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_QUES, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, _______, KC_MUTE, _______ \
      ),

  /* Symbol
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Del  |      |  \   |  |   |      |             |  ~   |  )   |  ]   |  }   |  >   |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Left | Down |  Up  |Right |      |             | ---- |  (   |  [   |  {   |  <   |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |  `   |  :   |  ,   |  .   |  ;   |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Prev |      | Mute |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_SYMBOL] = LAYOUT( \
      _______, KC_DEL,  _______, KC_BSLS, KC_PIPE, _______,                   KC_TILD, KC_RPRN, KC_RBRC, KC_RCBR, KC_GT,   _______, \
      _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, _______,                   _______, KC_LPRN, KC_LBRC, KC_LCBR, KC_LT,   _______, \
      _______, _______, _______, _______, _______, _______,                   KC_GRV,  KC_COLN, KC_COMM, KC_DOT,  KC_SCLN, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, _______, KC_MUTE, _______ \
      ),

  /* Shots Left:          macOS                                              Emacs, GNU Screen
   * ,--------------------------------------------.             ,-----------------------------------------.
   * |      |G-C-S-4|C-S-TAB| C-TAB |      |      |             |      |C-SPC | C-[  | M-RET|      |      |
   * |------+-------+-------+-------+------+------|             |------+------+------+------+------+------|
   * |      | ESC   |  JA   |  EN   | XXXX |      |             | C-g  | C-h  | C-z  | C-m  | M-x  |      |
   * |------+-------+-------+-------+------+------|             |------+------+------+------+------+------|
   * |      |       |S-Left |S-Rght |      |      |             |      | C-c  | C-,  | C-.  | C-/  |      |
   * |------+-------+-------+-------+------+------+-------------+------+------+------+------+------+------|
   * |      |       |       |       |      | C-3  |      |      |      |      |      |      |      |      |
   * `----------------------------------------------------------------------------------------------------'
   */
  [_SHOTL] = LAYOUT( \
      _______, G_C_S_4, C_S_TAB, C_TAB,   _______, _______,                   _______, C_SPC,   C_LBRC,  M_RET,   _______, _______, \
      _______, KC_ESC,  JA,      EN,      XXXXXXX, _______,                   C_G,     C_H,     C_Z,     C_M,     M_X,     _______, \
      _______, _______, SH_LEFT, SH_RGHT, _______, _______,                   _______, C_C,     C_COMM,  C_DOT,   C_SLSH,  _______, \
      _______, _______, _______, _______, _______, C_3,     _______, _______, _______, _______, _______, _______, _______, _______ \
      ),



  /* Shots Right:                                                       QuickSilver, Slack, Browser
   * ,-------------------------------------------.             ,------------------------------------------.
   * |      |       |      |       |      |      |             |      |      |G_S_Ent|      |      |      |
   * |------+-------+------+-------+------+------|             |------+------+-------+------+------+------|
   * |      |       |      |       |      |      |             |      | XXXX | C-3   |GUI-K |      |      |
   * |------+-------+------+-------+------+------|             |------+------+-------+------+------+------|
   * |      |       |      |       |      |      |             |      |      | GUI-1 |GUI-2 |GUI-3 |      |
   * |------+-------+------+-------+------+------+-------------+------+------+-------+------+------+------|
   * |      |       |      |       |      |      |      |      |      |      |       |      |      |      |
   * `----------------------------------------------------------------------------------------------------'
   */
  [_SHOTR] = LAYOUT( \
      _______, _______, _______, _______, _______, _______,                   _______, _______, G_S_ENT, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, XXXXXXX, C_3,     GUI_K,   _______, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, GUI_1,   GUI_2  , GUI_3,   _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
      ),

  /* Mouse keys
   * ,-------------------------------------------.             ,------------------------------------------.
   * |      |       |      | WH U  |      |      |             |      |      | MS U  |      |      |      |
   * |------+-------+------+-------+------+------|             |------+------+-------+------+------+------|
   * |      |       | WH L | BTN 1 | WH R |      |             |      | MS L | BTN 2 | MS R |      |      |
   * |------+-------+------+-------+------+------|             |------+------+-------+------+------+------|
   * |      |       |      | WH D  |      |      |             |      |      | MS D  |      |      |      |
   * |------+-------+------+-------+------+------+-------------+------+------+-------+------+------+------|
   * |      |-MOUSE |      |       |      |      |      |      |      | Left | Down  |  Up  | Rght |      |
   * `----------------------------------------------------------------------------------------------------'
   */
  [_MOUSE] = LAYOUT( \
      _______, _______,  _______, KC_WH_U, _______, _______,                   _______, _______, KC_MS_U, _______, _______, _______, \
      _______, _______,  KC_WH_L, KC_BTN1, KC_WH_R, _______,                   _______, KC_MS_L, KC_BTN2, KC_MS_R, _______, _______, \
      _______, _______,  _______, KC_WH_D, _______, _______,                   _______, _______, KC_MS_D, _______, _______, _______, \
      _______, MOUSE_T,  _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______ \
      ),

  /* Adjust
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |Aud on|Audoff|MU TOG|MU MOD| Mac  |             | Win  |Qwerty|      |EucalX|      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |CK TOG|CK RST| CK UP|CK DWN|      |             |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      _______, RESET,   _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, AU_ON,   AU_OFF,  MU_TOG,  MU_MOD,  AG_NORM,                   AG_SWAP, QWERTY,  _______, EUCALX,  _______, _______, \
      _______, CK_TOGG, CK_RST,  CK_UP,   CK_DOWN, _______,                   _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
      )
};



#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_eucalx[][2]     = SONG(DVORAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
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
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case EUCALX:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_eucalx);
        #endif
        persistent_default_layer_set(1UL<<_EUCALX);
      }
      return false;
      break;
    case SYMBOL:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_SYMBOL);
        update_tri_layer_RGB(_SYMBOL, _CURNUM, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_SYMBOL);
        update_tri_layer_RGB(_SYMBOL, _CURNUM, _ADJUST);
      }
      return false;
      break;
    case CURNUM:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_CURNUM);
        update_tri_layer_RGB(_SYMBOL, _CURNUM, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_CURNUM);
        TOG_STATUS = false;
        update_tri_layer_RGB(_SYMBOL, _CURNUM, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
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
    case EISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(50); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


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
#define L_SYMBOL (1<<_SYMBOL)
#define L_CURNUM (1<<_CURNUM)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_CURNUM|L_SYMBOL)

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
        case L_CURNUM:
           matrix_write_P(matrix, PSTR("CurNum"));
           break;
        case L_SYMBOL:
           matrix_write_P(matrix, PSTR("Symbol"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
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
