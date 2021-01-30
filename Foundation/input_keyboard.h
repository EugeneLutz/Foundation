//
//  input_keyboard.h
//  Foundation
//
//  Created by Евгений Лютц on 20.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef input_keyboard_h
#define input_keyboard_h

#include "private_interface.h"

typedef struct INPUT_KEYBOARD
{
	KEY_ACTION action;
	KEY_BUTTON_TYPE buttonType;
	unsigned int buttonKeyCode;
}
INPUT_KEYBOARD;

#endif /* input_keyboard_h */
