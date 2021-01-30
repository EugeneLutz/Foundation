//
//  input_keyboard.c
//  Foundation
//
//  Created by Евгений Лютц on 23.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

KEY_ACTION inputKeyboardGetAction(INPUT_KEYBOARD* inputKeyboard)
{
	assert(inputKeyboard != NULL);
	return inputKeyboard->action;
}

KEY_BUTTON_TYPE inputKeyboardGetKeyButtonType(INPUT_KEYBOARD* inputKeyboard)
{
	assert(inputKeyboard != NULL);
	return inputKeyboard->buttonType;
}

unsigned int inputKeyboardGetButtonKeyCode(INPUT_KEYBOARD* inputKeyboard)
{
	assert(inputKeyboard != NULL);
	return inputKeyboard->buttonKeyCode;
}
