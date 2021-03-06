//
//  input_responder.h
//  Foundation
//
//  Created by Евгений Лютц on 20.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef input_responder_h
#define input_responder_h

#include "private_interface.h"

typedef struct INPUT_DATA
{
	SF_ARRAY_DEF(INPUT_COMMAND, commands)
	SF_ARRAY_DEF(INPUT_KEYBOARD, keyboardCommands)
	SF_ARRAY_DEF(INPUT_MOUSE, mouseCommands)
	SF_ARRAY_DEF(INPUT_TOUCH, touchCommands)
}
INPUT_DATA;

typedef struct INPUT_RESPONDER
{
	SYSTEM* system;
	SEMAPHORE* accessSemaphore;
	
	void* userInfo;
	INPUT_RESPONDER_DELEGATE_FUNC delegate;
	
	INPUT_DATA* stashedCommands;	// Accumulating commands
	INPUT_DATA* inputHistory;		// Previously accumulated commands
	
	// MARK: - Tracking user input
	
	//SF_ARRAY_DEF(INPUT_COMMAND, inputHistory);
	
	// MARK: 1. Keyboard tracking
	
	/**
	 @abstract 
	 @discussion Array of @b TRACKING_KEYBOARD_BUTTON elements.
	*/
	MAGIC_ARRAY trackingKeyboardButtons;
	//SF_ARRAY_DEF(TRACKING_KEYBOARD_BUTTON*, trackingKeyboardButtons);
	
	// MARK: 2. Mouse tracking
	
	float mouseX;
	float mouseY;
	float mouseMoveX;
	float mouseMoveY;
	float mouseScrollX;
	float mouseScrollY;
	
	// SF_ARRAY_DEF(TRACKING_MOUSE_BUTTON, trackingMouseButtons);
	
	// MARK: 3. Touch tracking
	
	//SF_ARRAY_DEF(INPUT_TOUCH, touchHistory);
	
	// TODO: Add gamepad support
}
INPUT_RESPONDER;

#endif /* input_responder_h */
