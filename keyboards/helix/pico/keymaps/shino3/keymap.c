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
    _FINCOL = 0,
    _QWERTY,
    _SYMBOL,
    _EXTRA,
    _ADJUST
};

enum custom_keycodes {
  FINCOL = SAFE_RANGE,
  QWERTY,
  SYMBOL,
  EXTRA,
  ADJUST,
  BACKLIT,
  RGBRST,
  // C-x -> C-s
  CXCS,
  // Gui-L -> % -> Spc
  GLPS
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


// Spaces
#define SP_LCTL LCTL_T(KC_SPC)
#define SP_STAR LT(_SYMBOL, KC_SPC)
#define SP_RCTL RCTL_T(KC_SPC)
#define SP_RALT RALT_T(KC_SPC)
#define SP_EX   LT(_EXTRA, KC_SPC)

// En/Ja
/* #define EN       LCTL(LSFT(KC_SCLN))    // IME: En */
/* #define JA       LCTL(LSFT(KC_J))       // IME: Ja */
#define EN       KC_LANG2    // IME: En
#define JA       KC_LANG1    // IME: Ja

// FOURCOL : LT mods

#define A_SFT    LSFT_T(KC_A)
#define B_ALT    LALT_T(KC_B)
#define C_EX     LT(_EXTRA, KC_C)
#define F_EX     LT(_EXTRA, KC_F)
#define G_ALT    LALT_T(KC_G)

#define I_SFT    LSFT_T(KC_I)
#define J_EX     LT(_EXTRA, KC_J)
#define L_GUI    LGUI_T(KC_L)
#define L_ALT    LALT_T(KC_L)

#define O_LCTL   LCTL_T(KC_O)
#define Q_ALT    LALT_T(KC_Q)
#define Q_EX     LT(_EXTRA, KC_Q)
#define T_SFT    LSFT_T(KC_T)
#define U_GUI    LGUI_T(KC_U)
#define U_GUI    LGUI_T(KC_U)
#define U_LCTL   LCTL_T(KC_U)

#define V_EX     LT(_EXTRA, KC_V)
#define W_ALT    LALT_T(KC_W)
#define X_ST     LT(_SYMBOL, KC_X)
#define X_SFT    LSFT_T(KC_X)
#define X_ALT    LALT_T(KC_X)
#define Z_EX     LT(_EXTRA, KC_Z)
#define Z_ST     LT(_SYMBOL,  KC_Z)
#define Z_SFT    LSFT_T(KC_Z)
#define Z_GUI    LGUI_T(KC_Z)

#define MINS_ALT LALT_T(KC_MINS)
#define MINS_GUI LGUI_T(KC_MINS)
#define EN_GUI   LGUI_T(EN)
#define JA_GUI   LGUI_T(JA)
#define TB_GUI   LGUI_T(KC_TAB)
#define TB_ALT   LALT_T(KC_TAB)
#define JA_ALT   LALT_T(JA)
#define JA_GUI   LGUI_T(JA)
#define JA_SFT   LSFT_T(JA)

#define ZERO_SFT LSFT_T(KC_0)
#define DOT_SFT  LSFT_T(KC_DOT)
#define SLSH_SFT LSFT_T(KC_SLSH)

#define ESC_ALT  LALT_T(KC_ESC)
#define ESC_GUI  LGUI_T(KC_ESC)
#define ESC_EX   LT(_EXTRA, KC_ESC)
#define TAB_EX   LT(_EXTRA, KC_TAB)
#define F12_CTL  LCTL_T(KC_F12)

// QWERTY : LT mods

#define B_ALT    LALT_T(KC_B)
#define P_SFT    LSFT_T(KC_P)
#define V_ALT    LALT_T(KC_V)

// macOS
#define GUI_ENT  LGUI(KC_ENT)
#define G_MINS   LGUI(KC_MINS)
#define G_PLUS   LGUI(KC_PLUS)
#define GCS4     LGUI(LCTL(LSFT(KC_4))) // Screen capture

// Workspaces
#define GUI_0    LGUI(KC_0)
#define GUI_1    LGUI(KC_1)
#define GUI_2    LGUI(KC_2)
#define GUI_3    LGUI(KC_3)
#define GUI_4    LGUI(KC_4)
#define GUI_5    LGUI(KC_5)
#define GUI_6    LGUI(KC_6)
#define GUI_7    LGUI(KC_7)
#define GUI_8    LGUI(KC_8)
#define GUI_9    LGUI(KC_9)

// IME
#define SH_LEFT  LSFT(KC_LEFT)
#define SH_RGHT  LSFT(KC_RGHT)

// Launcher
#define C_3      LCTL(KC_3)
#define GUI_3    LGUI(KC_3)
#define C_RBRC   LCTL(KC_RBRC)

// Browsers
#define G_LBRC   LGUI(KC_LBRC)
#define G_RBRC   LGUI(KC_RBRC)
#define C_TAB    LCTL(KC_TAB)
#define CS_TAB   LCTL(LSFT(KC_TAB))
#define GS_T     LGUI(LSFT(KC_T))

// Slack
#define GUI_K    LGUI(KC_K)             // Jump
#define GS_ENT   LGUI(LSFT(KC_ENT))     // Create snippet

// Emacs
#define C_SPC    LCTL(KC_SPC)
#define C_C      LCTL(KC_C)
#define C_G      LCTL(KC_G)
#define C_H      LCTL(KC_H)
#define C_L      LCTL(KC_L)
#define C_M      LCTL(KC_M)
#define C_X      LCTL(KC_X)
#define C_U      LCTL(KC_U)
#define C_V      LCTL(KC_V)
#define C_Z      LCTL(KC_Z)

#define C_COMM   LCTL(KC_COMM)
#define C_DOT    LCTL(KC_DOT)
#define C_SLSH   LCTL(KC_SLSH)
#define C_SCLN   LCTL(KC_SCLN)
#define M_X      RALT(KC_X)
#define M_RET    RALT(KC_ENT)
#define M_LT     RALT(KC_LT)
#define M_GT     RALT(KC_GT)

// Extra
#define EX_T     TG(_EXTRA)
#define B2_ALT   RALT(KC_BTN2)

// Symbol
#define SYMB_T   TG(_SYMBOL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Mind Model: 3 x 4 + 3 per hand
   * ,-----------------------.                          ,-----------------------.
   * | Esc |  G  |  D  |  Y  |                          |  B  |  N  |  P  |  F  |
   * |-----+-----+-----+-----|                          |-----+-----+-----+-----|
   * |  A  |  I  |  U  |  E  |                          |  M  |  S  |  R  |  T  |
   * |-----+-----+-----+-----|                          |-----+-----+-----+-----|
   * |  Q  |  Z  |  W  |  X  |                          |  H  |  J  |  K  |  L  |
   * `-----------------------'                          `-----+-----------------'
   *                   +-----------------.  ,-----------------+
   *                   |  V  |  O  | En  |  | Ja  | Spc |  C  |
   *                   `-----------------'  `-----------------'
   */
  /* FinCol:
   * ,-----------------------------------.           ,-----------------------------------.
   * | Vo+ | Tab |  G  |  D  |  Y  | Sp  |           |  ,  |  B  |  N  |  P  | BS  | up  |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * | Vo- | Esc |  I  |  U  |  E  |caps |           |  .  |  M  |  S  |  R  |  F  |down |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * | +Ex |A/SF |  Z  |  W  |  X  |-Adj-|           |-Ply-|  H  |  J  |  K  |T/SF | +SY |
   * |-----+-----+-----+-----+-----+-----+-----------+-----+-----+-----+-----+-----+-----|
   * |caps |  Q  | Prv | Nxt |V/EX |O/CT |En/GU|Ja/AL|Sp/SY|C/EX |left |rght |  L  | Ent |
   * `-----------------------------------------------------------------------------------'
   */
  [_FINCOL] = LAYOUT( \
      KC_VOLU, KC_TAB,  KC_G,    KC_D,    KC_Y,    KC_SPC,                  KC_COMM, KC_B,    KC_N,    KC_P,    KC_BSPC,  KC_UP,   \
      KC_VOLD, KC_ESC,  KC_I,    KC_U,    KC_E,    KC_CAPS,                 KC_DOT,  KC_M,    KC_S,    KC_R,    KC_F,     KC_DOWN, \
      EX_T,    A_SFT,   KC_Z,    KC_W,    KC_X,    ADJUST,                  KC_MPLY, KC_H,    KC_J,    KC_K,    T_SFT,    SYMB_T,  \
      KC_CAPS, KC_Q,    KC_MPRV, KC_MNXT, V_EX,    O_LCTL,  EN_GUI, JA_ALT, SP_STAR, C_EX,    KC_LEFT, KC_RGHT, KC_L,     KC_ENT   \
      ),

  /* Qwerty:
   * ,-----------------------------------.           ,-----------------------------------.
   * | Mute| Vol-| Vol+| Prev| Play| Next|           | Del | Left| Down|  Up |Right| Adj |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * | Tab |  Q  |  W  |  E  |  R  |  T  |           |  Y  |  U  |  I  |  O  |  -  |     |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * |[Ex] |A/Sft|  S  |  D  | F/Ex|  G  |           |  H  | J/Ex|  K  |  L  |P/Sft|[EX] |
   * |-----+-----+-----+-----+-----+-----+-----------+-----+-----+-----+-----+-----+-----|
   * | Esc |  Z  |  X  |  C  | V/Al|Sp/Ct|EN/Sy|JA/Gu|Sp/St| B/Al|  N  |  M  |  /  | Ent |
   * `-----------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT,                 KC_DEL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  ADJUST,  \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_MINS,  _______, \
      EX_T,    A_SFT,   KC_S,    KC_D,    F_EX,    KC_G,                    KC_H,    J_EX,    KC_K,    KC_L,    P_SFT,    EX_T,    \
      KC_ESC,  KC_Z,    KC_X,    KC_C,    V_ALT,   SP_LCTL, EN_GUI, JA_GUI, SP_STAR, B_ALT,   KC_N,    KC_M,    KC_SLSH,  KC_ENT   \
      ),

  /* Symbol:        Numbers                                   Arith Ops, Parens
   * ,-----------------------------------.           ,-----------------------------------.
   * |     |     | 4 $ | 5 % | 6 ^ |     |           |     | = + | [ { | ] } |     |     |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * |     |     | 1 ! | 2 @ | 3 # |     |           |     | - _ | , < | . > | \ | |     |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * |     | 0 ) | 7 & | 8 * | 9 ( |     |           |     | F12 | ` ~ | ' " | / ? | ~SY |
   * |-----+-----+-----+-----+-----+-----+-----------+-----+-----+-----+-----+-----+-----|
   * |     |caps |     |     | C-v |F12/C|     |     | *** |     |     |     | ; : |     |
   * `-----------------------------------------------------------------------------------'
   */
  [_SYMBOL] = LAYOUT( \
      _______, _______,  KC_4,    KC_5,    KC_6,    _______,                   _______, KC_EQL,  KC_LBRC, KC_RBRC, _______,  _______, \
      _______, _______,  KC_1,    KC_2,    KC_3,    _______,                   _______, KC_MINS, KC_COMM, KC_DOT,  KC_BSLS,  _______, \
      _______, ZERO_SFT, KC_7,    KC_8,    KC_9,    _______,                   _______, KC_F12,  KC_GRV, KC_QUOT , SLSH_SFT, SYMB_T,  \
      _______, KC_CAPS,  _______, _______, C_V,     F12_CTL, _______, _______, _______, _______, _______, _______, KC_SCLN,  _______  \
      ),


  /* Extra:          Misc.                                            Move
   * ,-----------------------------------.           ,-----------------------------------.
   * |     |     |     |     |     |     |           |     | ⇇  | ⇊  | ⇈  |     |     |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * |     |     |GU-L%|GU-+ |GU-- |     |           |     | ⇦  | ⇩  | ⇧  | ⇉  |     |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * | ~EX |     |     |CS-Tb|C-Tb |     |           |     | ←  | ↓  | ↑  | ⇨  |     |
   * |-----+-----+-----+-----+-----+-----+-----------+-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |     |B2/AL| B1  |     |     |     | →  |     |
   * `-----------------------------------------------------------------------------------'
   */
  [_EXTRA] = LAYOUT( \
      _______, _______, _______, _______, _______, _______,                   _______, KC_WH_L, KC_WH_D, KC_WH_U, _______, _______, \
      _______, _______, GLPS,    G_PLUS,  G_MINS,  _______,                   _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_WH_R, _______, \
      EX_T,    _______, _______, CS_TAB,  C_TAB,   _______,                   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_MS_R, _______, \
      _______, _______, _______, _______, _______, _______, _______, B2_ALT,  KC_BTN1, _______, _______, _______, KC_RGHT, _______  \
      ),

  /* Adjust:
   * ,-----------------------------------.           ,-----------------------------------.
   * |     |Reset|     |     |     |     |           |     |     |     |     |     |     |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * |     |Audon|Audof|MUTOG|MUMOD| Mac |           | Win |Qwert|     | F/C |     |     |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * |     |CKTOG|CKRST|CK UP|CKDWN|     |           |     |     |RGBON|HUE+ |SAT+ |VAL+ |
   * |-----+-----+-----+-----+-----+-----+-----------+-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |     |     |     |     |MODE |HUE- |SAT- |VAL- |
   * `-----------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      _______, RESET,   _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, AU_ON,   AU_OFF,  MU_TOG,  MU_MOD,  AG_NORM,                   AG_SWAP, QWERTY,  _______, FINCOL,   _______, _______, \
      _______, CK_TOGG, CK_RST,  CK_UP,   CK_DOWN, _______,                   _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD  \
      )
};


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_fincol[][2]     = SONG(DVORAK_SOUND);
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
    case FINCOL:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_fincol);
        #endif
        persistent_default_layer_set(1UL<<_FINCOL);
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
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case GLPS:
      if (record->event.pressed) {
        // Change to EN mode first
        tap_code(KC_LANG2);
        // GUI-L
        register_code(KC_LGUI);
        tap_code(KC_L);
        unregister_code(KC_LGUI);
        // % and SPACE
        register_code(KC_LSFT);
        tap_code(KC_5);
        unregister_code(KC_LSFT);
        tap_code(KC_SPC);
      }
      return false;
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
#define L_SYMBOL  (1<<_SYMBOL)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_SYMBOL)

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
