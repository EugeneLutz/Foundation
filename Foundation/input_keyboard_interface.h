//
//  input_keyboard_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 23.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef input_keyboard_interface_h
#define input_keyboard_interface_h

#include "foundation.h"

KEY_ACTION inputKeyboardGetAction(INPUT_KEYBOARD* inputKeyboard);
KEY_BUTTON_TYPE inputKeyboardGetKeyButtonType(INPUT_KEYBOARD* inputKeyboard);
unsigned int inputKeyboardGetButtonKeyCode(INPUT_KEYBOARD* inputKeyboard);

#endif /* input_keyboard_interface_h */
