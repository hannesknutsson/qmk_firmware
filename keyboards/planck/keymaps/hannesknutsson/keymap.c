/* Copyright 2020 Hannes Knutsson
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
#include "keymap_swedish.h"

enum planck_layers {
  _BASE,
  _GAME,
  _LOWER,
  _RAISE,
  _BOTH
};

#define LOWER 		MO(_LOWER)		//Momentarily change to lower layer
#define RAISE 		MO(_RAISE)		//Momentarily change to raise layer

#define DEF_GAME  	TO(_GAME)		//Change default layer to game layer
#define DEF_BASE  	TO(_BASE)		//Change define layer to base layer

#define MT_RSH_ENT 	MT(MOD_RSFT, KC_ENTER)	//Right shift acts like enter when tapped

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	//Base layer containing letters, modifiers and basic punctuation.
	[_BASE] = LAYOUT_planck_grid(
	    KC_TAB ,  SE_Q   , SE_W   , SE_E   , SE_R , SE_T  , SE_Y  , SE_U , SE_I   , SE_O   , SE_P 	, SE_ARNG   ,
	    KC_LCTL,  SE_A   , SE_S   , SE_D   , SE_F , SE_G  , SE_H  , SE_J , SE_K   , SE_L   , SE_ODIA, SE_ADIA   ,
	    KC_LSFT,  SE_Z   , SE_X   , SE_C   , SE_V , SE_B  , SE_N  , SE_M , SE_COMM, SE_DOT , SE_MINS, MT_RSH_ENT,
	    KC_ESC ,  KC_LGUI, KC_LALT, XXXXXXX, LOWER, KC_SPC, KC_SPC, RAISE, KC_ALGR, XXXXXXX, XXXXXXX, DEF_GAME
	),

	//Game layer. Shifts top three rows down one row to allow for a persistent number row.
	[_GAME] = LAYOUT_planck_grid(
	    KC_ESC ,  SE_1, SE_2, SE_3, SE_4, SE_5  , SE_6  , SE_7, SE_8   , SE_9  , SE_0   , SE_PLUS   ,
	    KC_TAB ,  SE_Q, SE_W, SE_E, SE_R, SE_T  , SE_Y  , SE_U, SE_I   , SE_O  , SE_P   , SE_ARNG   ,
	    KC_LSFT,  SE_A, SE_S, SE_D, SE_F, SE_G  , SE_H  , SE_J, SE_K   , SE_L  , SE_ODIA, MT_RSH_ENT,
	    KC_LCTL,  SE_Z, SE_X, SE_C, SE_V, KC_SPC, KC_SPC, SE_M, SE_COMM, SE_DOT, SE_MINS, DEF_BASE
	),

	//Raise layer containing special characters and arrow keys.
	[_RAISE] = LAYOUT_planck_grid(
	    _______, _______, _______, SE_LPRN, SE_RPRN, _______, _______, _______, _______, _______ , _______, KC_DEL ,
	    _______, SE_PIPE, _______, SE_LCBR, SE_RCBR, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT, _______, KC_BSPC,
	    _______, SE_LABK, SE_RABK, SE_LBRC, SE_RBRC, _______, _______, _______, _______, _______ , _______, _______,
	    _______, _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______ , _______, _______
	),

	//Lower layer containing numbers, F-keys, backspace and delete.
	[_LOWER] = LAYOUT_planck_grid(
	    _______, SE_1   , SE_2   , SE_3   , SE_4   , SE_5   , SE_6   , SE_7  , SE_8   , SE_9   , SE_0   , SE_PLUS,
	    _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , SE_4  , SE_5   , SE_6   , SE_DIAE, SE_ACUT,
	    _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , SE_1  , SE_2   , SE_3   , SE_QUOT, _______,
	    _______, _______, _______, _______, _______, _______, _______, SE_DOT, _______, _______, _______, _______
	),

	//Combined layer. Activates when both lower and raise activates at the same time.
	[_LOWER] = LAYOUT_planck_grid(
	    RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______ , _______, _______,
	    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ , _______, _______,
	    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ , _______, _______,
	    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ , _______, _______
	)


};

//Tells QMK what to do when bothe lower and raise is active at the same time (activates _BOTH).
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _BOTH);
}
