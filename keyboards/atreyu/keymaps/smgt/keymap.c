/* Copyright 2022 Jesus Climent  (@climent)
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


enum custom_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LWR,
  RSE,
  ADJ
};

#define KC_LOWR _LOWER
#define KC_RASE _RAISE


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
     QK_GESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0    ,KC_MINS  ,
     KC_TAB  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P    ,KC_DEL ,
     KC_LCTL , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN ,KC_QUOT ,
     KC_GRV  , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH ,KC_RSFT ,
     KC_LCTL,           KC_LOWR, KC_RASE, KC_BSPC, KC_LOWR, KC_RGUI, KC_LGUI, KC_ENT , KC_SPC , KC_LALT,  KC_NO ,          KC_RCTL
  ),

[_LOWER] = LAYOUT(
  KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
  QK_BOOT, _______, _______, _______, _______, _______,                   KC_EQL , KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_BSLS,
  KC_DEL , _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, KC_PIPE,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______,          _______, _______, _______, _______, _______, _______, KC_DEL , _______, KC_P0  , _______, _______
),

[_RAISE] = LAYOUT(
  KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                   KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
  _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS,
  _______, KC_MPRV, KC_MNXT, KC_VOLU, KC_PGUP, KC_UNDS,                   KC_EQL , KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, KC_PGDN, KC_MINS,                   KC_PLUS, KC_END , _______, _______, _______, _______,
  _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______
),

[_ADJUST] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______,          _______, _______, _______, _______ , _______, _______ , _______, _______, _______, _______,         _______
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case _QWERTY:
      if (record->event.pressed) {
        //persistent_default_layer_set(1UL<<_QWERTY);
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case _LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case _RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case _ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
  // switch (keycode) {
  //   case LWR:
  //     if (record->event.pressed) {
  //       layer_on(_LOWER);
  //       update_tri_layer(_LOWER, _RAISE, _ADJUST);
  //     } else {
  //       layer_off(_LOWER);
  //       update_tri_layer(_LOWER, _RAISE, _ADJUST);
  //     }
  //     return false;
  //     break;
  //
  //   case RSE:
  //     if (record->event.pressed) {
  //       layer_on(_RAISE);
  //       update_tri_layer(_LOWER, _RAISE, _ADJUST);
  //     } else {
  //       layer_off(_RAISE);
  //       update_tri_layer(_LOWER, _RAISE, _ADJUST);
  //     }
  //     return false;
  //     break;
  //
  //   case KC_ESC:
  //    if ((get_mods() & MOD_BIT(KC_LGUI)) == MOD_BIT(KC_LGUI)) {
  //       if (record->event.pressed) {
  //         register_code(KC_GRV);
  //       } else {
  //         unregister_code(KC_GRV);
  //       }
  //       return false;
  //     }
  //     return true;
  //     break;
  // }
  // return true;
}

#ifdef OLED_ENABLE
// static void render_logo(void) {
//     static const char PROGMEM raw_logo[] = {
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//     };
//     oled_write_raw_P(raw_logo, sizeof(raw_logo));
// }

// Liv tree
// static void render_logo(void) {
//     static const char PROGMEM raw_logo[] = {
//         15, 24,224, 64,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 70, 56, 48, 30, 17, 12,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224, 56, 38,161,144,136,164,148,238,115,109,211, 81, 72,100,100, 34, 34, 49, 48, 48,168,168, 88,126, 55, 62, 26, 52, 52, 40,100,100,100,102,196,196,196,200,132,132,252,132,132,130,130,130,  0,
//         0, 63,192,  0,  0, 29,225,  1,  1,  1,  3,  1,  1,  1, 63,255,  7,  1,129,  1,  1, 15,  1,  1,  1,  1,225,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1, 31,255, 63,  1,  1,  1,  1,  1,  1,255, 63,  3,  1,  1,  1,  1,  1,  1,  1,  1, 15,  1,255, 15,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3, 63,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33, 33,144,140,131, 64, 64, 32, 32, 16, 17,137,  9,  5,133,  3,  3,  3, 35, 30, 39, 34, 35, 67, 81, 81, 81, 73, 75,130,130,194,194,196,196, 68,124, 36, 36, 24, 24, 24,  8, 48, 40, 65,
//         0,  0, 31,  0,  0,128,255,128,128,128,128,128,224,128,128,135,128,128,255,248,128,128,128,128,128,128,135,252,240,128,128,128,128,224,128,128,128,128,129,128,128,128,192,128,128,128,131,156,128,128,128,128,128,128,128,128,128,128,128,129,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,192,195,133,136,144,160,192,  8,  8,148,152, 40, 48, 96,193,129,  2,  2,  6, 70, 70,134,158, 46, 86, 86,162, 66,130,133, 69, 69, 73,104, 88,166,161,161,145,209,209, 82, 74, 66, 34, 34, 18,
//         18,243, 28,  4,  2,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,129,226, 82, 12,  4,120,144, 16, 16, 16, 48,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  2,  4,  4, 24, 48,200,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 31, 33,200, 17, 34, 68,136, 17, 35, 69,137, 55, 77,153,243, 37, 69,135, 10, 22, 46, 84,236, 77,137, 26, 52, 85,106,212, 25, 49, 50, 98,196,200,249,130,132,  4,  8,  9,  9, 18, 18, 36, 36,
//         4,
//     };
//     oled_write_raw_P(raw_logo, sizeof(raw_logo));
// }

// doge
// static void render_logo(void) {
//     static const char PROGMEM raw_logo[] = {
//         15, 24,224, 64,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 70, 56, 48, 30, 17, 12,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224, 56, 38,161,144,136,164,148,238,115,109,211, 81, 72,100,100, 34, 34, 49, 48, 48,168,168, 88,126, 55, 62, 26, 52, 52, 40,100,100,100,102,196,196,196,200,132,132,252,132,132,130,130,130,  0,
//         0, 63,192,  0,  0, 29,225,  1,  1,  1,  3,  1,  1,  1, 63,255,  7,  1,129,  1,  1, 15,  1,  1,  1,  1,225,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1, 31,255, 63,  1,  1,  1,  1,  1,  1,255, 63,  3,  1,  1,  1,  1,  1,  1,  1,  1, 15,  1,255, 15,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3, 63,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33, 33,144,140,131, 64, 64, 32, 32, 16, 17,137,  9,  5,133,  3,  3,  3, 35, 30, 39, 34, 35, 67, 81, 81, 81, 73, 75,130,130,194,194,196,196, 68,124, 36, 36, 24, 24, 24,  8, 48, 40, 65,
//         0,  0, 31,  0,  0,128,255,128,128,128,128,128,224,128,128,135,128,128,255,248,128,128,128,128,128,128,135,252,240,128,128,128,128,224,128,128,128,128,129,128,128,128,192,128,128,128,131,156,128,128,128,128,128,128,128,128,128,128,128,129,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,192,195,133,136,144,160,192,  8,  8,148,152, 40, 48, 96,193,129,  2,  2,  6, 70, 70,134,158, 46, 86, 86,162, 66,130,133, 69, 69, 73,104, 88,166,161,161,145,209,209, 82, 74, 66, 34, 34, 18,
//         18,243, 28,  4,  2,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,129,226, 82, 12,  4,120,144, 16, 16, 16, 48,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  2,  4,  4, 24, 48,200,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 31, 33,200, 17, 34, 68,136, 17, 35, 69,137, 55, 77,153,243, 37, 69,135, 10, 22, 46, 84,236, 77,137, 26, 52, 85,106,212, 25, 49, 50, 98,196,200,249,130,132,  4,  8,  9,  9, 18, 18, 36, 36,
//         4,
//     };
//     oled_write_raw_P(raw_logo, sizeof(raw_logo));
// }

// static void render_logo(void) {
//     static const char PROGMEM bananas_logo[] = {
//         // 'killmaster_bananas', 128x32px
//         0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xe0, 0x02, 0x0e, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
//         0x00, 0x00, 0x80, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x40, 0x40, 0xd8, 0xc8, 0x00, 0x00, 0x00, 0x00,
//         0x08, 0x08, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0xf8, 0xf8, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0xc0, 0x40, 0x40, 0xc0, 0x80, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40,
//         0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0xc0, 0x40, 0x00, 0x00, 0x40, 0x40, 0xf0,
//         0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0xc0, 0x80, 0x00, 0x00, 0x00,
//         0x40, 0xc0, 0x80, 0x40, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x01, 0x0f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xf0,
//         0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
//         0x02, 0x07, 0x0d, 0x10, 0x20, 0x20, 0x00, 0x00, 0x20, 0x20, 0x3f, 0x3f, 0x20, 0x20, 0x00, 0x00,
//         0x00, 0x00, 0x1f, 0x3f, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x20, 0x20, 0x20,
//         0x00, 0x00, 0x3f, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x1c, 0x36, 0x22, 0x22, 0x22,
//         0x1f, 0x20, 0x00, 0x00, 0x10, 0x23, 0x22, 0x22, 0x26, 0x3c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x1f,
//         0x30, 0x20, 0x20, 0x20, 0x00, 0x00, 0x0f, 0x1f, 0x32, 0x22, 0x22, 0x32, 0x23, 0x00, 0x00, 0x00,
//         0x20, 0x3f, 0x21, 0x20, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x1f, 0x1f,
//         0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3e, 0x3e, 0x1c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//         };
//     oled_write_raw_P(bananas_logo, sizeof(bananas_logo));
// }

// Skull
// static void render_logo(void) {
//     static const char PROGMEM skull[] = {
//     // 'skull-1bit', 32x12px
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0x0e, 0x0f, 0x9f, 0xff, 0x7f,
// 0xff, 0x9f, 0x0f, 0x0e, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x0f, 0x07, 0x0e, 0x04,
// 0x0e, 0x07, 0x0f, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//         };
//     oled_write_raw_P(skull, sizeof(skull));
// }

// static void render_logo(void) {
//     static const char PROGMEM raw_logo[] = {
//         // 'cat-1bit', 32x32px
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
// 0x90, 0xf0, 0x90, 0xf8, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x30, 0x48, 0x0c, 0x1e, 0x1e, 0x0e,
// 0x1e, 0x04, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//     };
//     oled_write_raw_P(raw_logo, sizeof(raw_logo));
// }

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        // 'cat-1bit', 32x32px
// 'smgt-cat-1bit', 32x24px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xdf, 0xd2,
0x9e, 0xd2, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xe0, 0xf0, 0x90, 0x10, 0x20, 0x00, 0xf0, 0xe0, 0xc0, 0x86, 0x09, 0x01, 0x83, 0xc3, 0xe1, 0xf3,
0x00, 0xe3, 0xf0, 0x10, 0x10, 0x10, 0x20, 0x00, 0x10, 0x10, 0xf0, 0xf0, 0x10, 0x10, 0x00, 0x00,
0x08, 0x11, 0x13, 0x1f, 0x0e, 0x00, 0x1f, 0x00, 0x01, 0x03, 0x07, 0x03, 0x01, 0x00, 0x1f, 0x1f,
0x00, 0x0f, 0x1f, 0x10, 0x11, 0x1f, 0x0f, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}



oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

// Luna, animated cat
// https://github.com/HellSingCoder/qmk_firmware/blob/master/keyboards/sofle/keymaps/helltm/keymap.c

bool oled_task_user(void) {
    render_logo();
    oled_set_cursor(0, 4);

    // // Host Keyboard Layer Status
    oled_write_P(PSTR("L;"), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("DEF\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOW\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAI\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("UKN"), false);
    }
    //
    oled_write_P(PSTR("W;"), false);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
    oled_write_P(PSTR("\n"), false);

    // // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM  ") : PSTR("     "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP  ") : PSTR("     "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR  ") : PSTR("     "), false);

    // static const char os_logo[][6] PROGMEM  ={
    //     {0x95,0x96,10,0xb5,0xb6,0}, //apple
    //     {0x99,0x9a,10,0xb9,0xba,0} //tux
    // };
    // oled_write_P(os_logo[0], false);
    // oled_write_P(PSTR("\n"), false);
    // oled_write_P(os_logo[1], false);
    return false;
}
#endif
