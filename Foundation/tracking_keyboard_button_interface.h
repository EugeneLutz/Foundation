//
//  tracking_keyboard_button_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 26.04.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef tracking_keyboard_button_interface_h
#define tracking_keyboard_button_interface_h

#include "foundation.h"

KEY_BUTTON_TYPE trackingKeyboardButtonGetButtonType(TRACKING_KEYBOARD_BUTTON* button);
unsigned int trackingKeyboardButtonGetKeyCode(TRACKING_KEYBOARD_BUTTON* button);

unsigned int trackingKeyboardButtonGetNumAccumulatedActions(TRACKING_KEYBOARD_BUTTON* button);
KEY_ACTION trackingKeyboardButtonGetCurrentActionType(TRACKING_KEYBOARD_BUTTON* button);
KEY_ACTION trackingKeyboardButtonGetAccumulatedActionType(TRACKING_KEYBOARD_BUTTON* button, unsigned int actionIndex);
double trackingKeyboardButtonGetAccumulatedActionTime(TRACKING_KEYBOARD_BUTTON* button, unsigned int actionIndex);

#endif /* tracking_keyboard_button_interface_h */
