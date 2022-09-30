/*
Copyright 2021 Bryan Ong

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN,
	_GAME
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_alice_split_bs(
        SGUI(KC_Q),KC_GRV,    	 KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_6,    		    	KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,
        KC_VOLU,   KC_ESCAPE, 	 KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_VOLD,   LT(_FN,KC_TAB),KC_A,	  KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN, KC_QUOT, KC_ENT,
                   KC_LSFT,   	 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_LGUI,    KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT, KC_DEL,
                   KC_LCTL,      KC_LALT,          LCTL_T(KC_SPC),   KC_BSPC,                       KC_SPC,  KC_RALT,                                               TO(_GAME)),
    [_FN] = LAYOUT_alice_split_bs(
        KC_TRNS,      SGUI(KC_S),KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,                 KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL,
        C(G(KC_RGHT)),LGUI(KC_R),KC_HOME, KC_UP,   KC_END,  KC_NO,   KC_NO,                         KC_ASTR, KC_7,    KC_8,    KC_9,    KC_PLUS, KC_NO,   KC_NO,   KC_NO,
        C(G(KC_LEFT)),KC_TRNS,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_F5,                         KC_PSLS, KC_4,    KC_5,    KC_6,    KC_MINS, KC_ENT,  KC_TRNS,
                      KC_CAPS,   KC_NO,   KC_PGUP, KC_PGDN, KC_NO, LGUI(KC_TAB),                    KC_NO,   KC_COLN, KC_1,    KC_2,    KC_3,    KC_NO,   KC_NO,    KC_NO,
                      LCA(KC_DEL),        LSFT(KC_DEL), LGUI(KC_E),KC_TRNS,                         KC_0,    KC_DOT,                                                KC_SLEP),
	[_GAME] = LAYOUT_alice_split_bs(
        KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 	        	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        C(G(KC_RGHT)), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        C(G(KC_LEFT)), KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
					   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                       KC_TRNS,                     KC_TRNS, KC_SPC, KC_TRNS,                       KC_TRNS, KC_TRNS,                                              TO(_BASE)),
};

// change LEDs based on layer
// Pins defined below
//#define LED_NUM_LOCK_PIN  D4
//#define LED_CAPS_LOCK_PIN D6
//#define LED_SCROLL_LOCK_PIN D7

void led_init_ports(void) {
    setPinOutput(D4);  // initialize B0 for Num Lock LED
    setPinOutput(D7);  // initialize B1 for Scroll Lock LED
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _GAME:
		    // set layer to _GAME light up num lock LED
			if (!host_keyboard_led_state().num_lock) {
				register_code(KC_NLCK);
				unregister_code(KC_NLCK);
			}
			//writePin(D4, 1);
            break;
        default:
			// if num_lock LED is on then disable
			if (host_keyboard_led_state().num_lock) {
				register_code(KC_NLCK);
				unregister_code(KC_NLCK);
			}
			//writePin(D4, 0);
			//writePin(D7, 0);
            break;
    }
	return state;
}


