//
//  tracking_keyboard_button.c
//  Foundation
//
//  Created by Евгений Лютц on 26.04.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

// MARK: - Private interface

void trackingKeyboardButtonInitialize(TRACKING_KEYBOARD_BUTTON* button, INPUT_RESPONDER* inputResponder, KEY_BUTTON_TYPE keyButtonType, unsigned int buttonKeyCode)
{
	assert(button);
	button->inputResponder = inputResponder;
	button->type = keyButtonType;
	button->keyCode = buttonKeyCode;
	button->currentAction = KEY_ACTION_UP;
	SF_ARRAY_INIT(KEYBOARD_BUTTON_TRACK_INFO, button->trackInfo, 16);
}

void trackingKeyboardButtonDeinitialize(TRACKING_KEYBOARD_BUTTON* button)
{
	assert(button);
	SF_ARRAY_RELEASE(button->trackInfo);
}

void trackingKeyboardButtonAddAction(TRACKING_KEYBOARD_BUTTON* button, KEY_ACTION action, double actionTime)
{
	assert(button);
	SF_ARRAY_PREPARE_NEXT(KEYBOARD_BUTTON_TRACK_INFO, button->trackInfo, 16);
	SF_ARRAY_STASH_NEXT(button->trackInfo);
	KEYBOARD_BUTTON_TRACK_INFO* trackInfo = &SF_ARRAY_LAST(button->trackInfo);
	trackInfo->action = action;
	trackInfo->actionTime = actionTime;
	
	button->currentAction = action;
}

void trackingKeyboardButtonReset(TRACKING_KEYBOARD_BUTTON* button)
{
	assert(button);
	SF_ARRAY_RESET(button->trackInfo);
}

// MARK: - Public interface

void trackingKeyboardButtonRelease(TRACKING_KEYBOARD_BUTTON* button)
{
	assert(button);
	
	trackingKeyboardButtonDeinitialize(button);
	magicArrayRemoveItem(&button->inputResponder->trackingKeyboardButtons, button);
}

KEY_BUTTON_TYPE trackingKeyboardButtonGetButtonType(TRACKING_KEYBOARD_BUTTON* button)
{
	assert(button);
	return button->type;
}

unsigned int trackingKeyboardButtonGetKeyCode(TRACKING_KEYBOARD_BUTTON* button)
{
	assert(button);
	return button->keyCode;
}

KEY_ACTION trackingKeyboardButtonGetCurrentActionType(TRACKING_KEYBOARD_BUTTON* button)
{
	assert(button);
	return button->currentAction;
}

unsigned int trackingKeyboardButtonGetNumAccumulatedActions(TRACKING_KEYBOARD_BUTTON* button)
{
	assert(button);
	return SF_ARRAY_LEN(button->trackInfo);
}

KEY_ACTION trackingKeyboardButtonGetAccumulatedActionType(TRACKING_KEYBOARD_BUTTON* button, unsigned int actionIndex)
{
	assert(button);
	return button->trackInfo[actionIndex].action;
}

double trackingKeyboardButtonGetAccumulatedActionTime(TRACKING_KEYBOARD_BUTTON* button, unsigned int actionIndex)
{
	assert(button);
	return button->trackInfo[actionIndex].actionTime;
}
