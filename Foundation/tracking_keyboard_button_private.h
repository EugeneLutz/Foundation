//
//  tracking_keyboard_button_private.h
//  Foundation
//
//  Created by Евгений Лютц on 26.04.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef tracking_keyboard_button_private_h
#define tracking_keyboard_button_private_h

#include "private_interface.h"

void trackingKeyboardButtonInitialize(TRACKING_KEYBOARD_BUTTON* button, INPUT_RESPONDER* inputResponder, KEY_BUTTON_TYPE keyButtonType, unsigned int buttonKeyCode);
void trackingKeyboardButtonDeinitialize(TRACKING_KEYBOARD_BUTTON* button);

void trackingKeyboardButtonAddAction(TRACKING_KEYBOARD_BUTTON* button, KEY_ACTION action, double actionTime);
void trackingKeyboardButtonReset(TRACKING_KEYBOARD_BUTTON* button);

#endif /* tracking_keyboard_button_private_h */
