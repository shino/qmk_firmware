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
#define C_SFT    LSFT_T(KC_C)
#define F_EX     LT(_EXTRA, KC_F)
#define G_ALT    LALT_T(KC_G)

#define I_SFT    LSFT_T(KC_I)
#define J_EX     LT(_EXTRA, KC_J)
#define L_GUI    LGUI_T(KC_L)
#define L_ALT    LALT_T(KC_L)

#define O_LCTL   LCTL_T(KC_O)
#define Q_ALT    LALT_T(KC_Q)
#define Q_EX     LT(_EXTRA, KC_Q)
#define R_SFT    LSFT_T(KC_R)
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
#define F12_SFT  LSFT_T(KC_F12)
#define F12_EX   LT(_EXTRA, KC_F12)
#define K0_GUI   LGUI_T(KC_0)
#define K9_CTL   LCTL_T(KC_9)
#define MNXT_EX   LT(_EXTRA, KC_MNXT)

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

// -- New ones below

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


#ifdef AUDIO_ENABLE

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
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_fincol);
        #endif
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
