//
//  tracking_keyboard_button.h
//  Foundation
//
//  Created by Евгений Лютц on 26.04.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef tracking_keyboard_button_h
#define tracking_keyboard_button_h

#include "private_interface.h"

typedef struct KEYBOARD_BUTTON_TRACK_INFO
{
	KEY_ACTION action;
	double actionTime;
}
KEYBOARD_BUTTON_TRACK_INFO;

typedef struct TRACKING_KEYBOARD_BUTTON
{
	/// Owner of this object (weak reference)
	INPUT_RESPONDER* inputResponder;
	
	KEY_BUTTON_TYPE type;
	unsigned int keyCode;
	KEY_ACTION currentAction;
	SF_ARRAY_DEF(KEYBOARD_BUTTON_TRACK_INFO, trackInfo);
}
TRACKING_KEYBOARD_BUTTON;

#endif /* tracking_keyboard_button_h */
