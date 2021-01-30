//
//  input_responder.c
//  Foundation
//
//  Created by Евгений Лютц on 20.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

INPUT_RESPONDER* inputResponderCreate(INPUT_RESPONDER_DELEGATE_FUNC delegate, void* userInfo, SYSTEM* system, EXECUTE_RESULT* executeResult)
{
	assert(system);
	
	SEMAPHORE* accessSemaphore = systemCreateSemaphore(system, 1);
	
	INPUT_RESPONDER* inputResponder = malloc(sizeof(INPUT_RESPONDER));
	inputResponder->system = system;
	inputResponder->accessSemaphore = accessSemaphore;
	inputResponder->delegate = delegate;
	inputResponder->userInfo = userInfo;
	
	INPUT_DATA* commands[2];
	for (int i = 0; i < 2; i++)
	{
		INPUT_DATA* data = malloc(sizeof(INPUT_DATA));
		commands[i] = data;
		
		SF_ARRAY_INIT(INPUT_COMMAND, data->commands, 64);
		SF_ARRAY_INIT(INPUT_KEYBOARD, data->keyboardCommands, 64);
		SF_ARRAY_INIT(INPUT_MOUSE, data->mouseCommands, 64);
		SF_ARRAY_INIT(INPUT_TOUCH, data->touchCommands, 64);
	}
	inputResponder->stashedCommands = commands[0];
	inputResponder->inputHistory = commands[1];
	
	
	SF_ARRAY_INIT(TRACKING_KEYBOARD_BUTTON*, inputResponder->trackingKeyboardButtons, 128);
	
	inputResponder->mouseX = 0.0f;
	inputResponder->mouseY = 0.0f;
	inputResponder->mouseMoveX = 0.0f;
	inputResponder->mouseMoveY = 0.0f;
	inputResponder->mouseScrollX = 0.0f;
	inputResponder->mouseScrollY = 0.0f;
	
	executeResultSetSucceeded(executeResult);
	return inputResponder;
}

void inputResponderRelease(INPUT_RESPONDER* inputResponder)
{
	assert(inputResponder);
	
	for (unsigned int i = 0; i < SF_ARRAY_LEN(inputResponder->trackingKeyboardButtons); i++)
	{
		TRACKING_KEYBOARD_BUTTON* currentButton = inputResponder->trackingKeyboardButtons[i];
		trackingKeyboardButtonRelease(currentButton);
	}
	SF_ARRAY_RELEASE(inputResponder->trackingKeyboardButtons);
	
	SF_ARRAY_RELEASE(inputResponder->inputHistory->touchCommands);
	SF_ARRAY_RELEASE(inputResponder->inputHistory->mouseCommands);
	SF_ARRAY_RELEASE(inputResponder->inputHistory->keyboardCommands);
	SF_ARRAY_RELEASE(inputResponder->inputHistory->commands);
	free(inputResponder->inputHistory);
	
	SF_ARRAY_RELEASE(inputResponder->stashedCommands->touchCommands);
	SF_ARRAY_RELEASE(inputResponder->stashedCommands->mouseCommands);
	SF_ARRAY_RELEASE(inputResponder->stashedCommands->keyboardCommands);
	SF_ARRAY_RELEASE(inputResponder->stashedCommands->commands);
	free(inputResponder->stashedCommands);
	
	semaphoreRelease(inputResponder->accessSemaphore);
	free(inputResponder);
}

//
// Delegate locking
//

void inputResponderResetInput(INPUT_RESPONDER* inputResponder)
{
	assert(inputResponder);
	
	semaphoreEnter(inputResponder->accessSemaphore);
	
	INPUT_DATA* data = inputResponder->stashedCommands;
	
	// Reset all accumulated data
	
	for (unsigned int i = 0; i < SF_ARRAY_LEN(inputResponder->trackingKeyboardButtons); i++)
	{
		TRACKING_KEYBOARD_BUTTON* currentButton = inputResponder->trackingKeyboardButtons[i];
		trackingKeyboardButtonReset(currentButton);
	}
	
	//inputResponder->mouseX = 0.0f;
	//inputResponder->mouseY = 0.0f;
	
	inputResponder->mouseMoveX = 0.0f;
	inputResponder->mouseMoveY = 0.0f;
	
	inputResponder->mouseScrollX = 0.0f;
	inputResponder->mouseScrollY = 0.0f;
	
	// If there are stashed commands
	if (data->commandsLen > 0)
	{
		for (unsigned int i = 0; i < SF_ARRAY_LEN(data->commands); i++)
		{
			INPUT_COMMAND* command = &(data->commands[i]);
			if (command->inputType == INPUT_COMMAND_TYPE_KEYBOARD)
			{
				INPUT_KEYBOARD* keyboardInput = (INPUT_KEYBOARD*)(command->inputData);
				for (unsigned int i = 0; i < SF_ARRAY_LEN(inputResponder->trackingKeyboardButtons); i++)
				{
					TRACKING_KEYBOARD_BUTTON* currentButton = inputResponder->trackingKeyboardButtons[i];
					if (currentButton->type == keyboardInput->buttonType &&
						currentButton->keyCode == keyboardInput->buttonKeyCode)
					{
						trackingKeyboardButtonAddAction(currentButton, keyboardInput->action, command->inputTime);
					}
				}
			}
			else if (command->inputType == INPUT_COMMAND_TYPE_MOUSE)
			{
				INPUT_MOUSE* mouseInput = (INPUT_MOUSE*)(command->inputData);
				if (mouseInput->action == MOUSE_ACTION_MOVE)
				{
					inputResponder->mouseX = mouseInput->xPosition;
					inputResponder->mouseY = mouseInput->yPosition;
					inputResponder->mouseMoveX += mouseInput->xMove;
					inputResponder->mouseMoveY += mouseInput->yMove;
				}
				else if (mouseInput->action == MOUSE_ACTION_SCROLL)
				{
					inputResponder->mouseScrollX += mouseInput->xScroll;
					inputResponder->mouseScrollY += mouseInput->yScroll;
				}
			}
		}
	}


	inputResponder->stashedCommands = inputResponder->inputHistory;
	inputResponder->inputHistory = data;
	
	// Reset input command counters
	data = inputResponder->stashedCommands;
	SF_ARRAY_RESET(data->commands);
	SF_ARRAY_RESET(data->keyboardCommands);
	SF_ARRAY_RESET(data->mouseCommands);
	SF_ARRAY_RESET(data->touchCommands);
	
	semaphoreLeave(inputResponder->accessSemaphore);
}

unsigned int inputResponderGetNumAccumulatedCommands(INPUT_RESPONDER* inputResponder)
{
	assert(inputResponder);
	return SF_ARRAY_LEN(inputResponder->inputHistory->commands);
}

INPUT_COMMAND* inputResponderGetAccumulatedCommand(INPUT_RESPONDER* inputResponder, unsigned int commandIndex)
{
	assert(inputResponder);
	return &(inputResponder->inputHistory->commands[commandIndex]);
}

//
// Keyboard input
//

void inputResponderKeyboardAction(INPUT_RESPONDER* inputResponder, KEY_ACTION action, KEY_BUTTON_TYPE buttonType, unsigned int buttonKeyCode)
{
	assert(inputResponder);
	
	semaphoreEnter(inputResponder->accessSemaphore);
	
	INPUT_DATA* inputData = inputResponder->stashedCommands;
	
	// 1. Fill keyboard input data
	SF_ARRAY_PREPARE_NEXT(INPUT_KEYBOARD, inputData->keyboardCommands, 32);
	INPUT_KEYBOARD* key = &SF_ARRAY_NEXT(inputData->keyboardCommands);
	key->action = action;
	key->buttonType = buttonType;
	key->buttonKeyCode = buttonKeyCode;
	
	// 2. Fill input command data
	SF_ARRAY_PREPARE_NEXT(INPUT_COMMAND, inputData->commands, 32);
	INPUT_COMMAND* command = &SF_ARRAY_NEXT(inputData->commands);
	command->inputType = INPUT_COMMAND_TYPE_KEYBOARD;
	command->inputData = key;
	command->inputTime = systemGetCurrentTime(inputResponder->system);
	
	// 3. Stash command
	SF_ARRAY_STASH_NEXT(inputData->keyboardCommands);
	SF_ARRAY_STASH_NEXT(inputData->commands);

	// 4. Delegate input event
	inputResponder->delegate(command, inputResponder->userInfo);
	
	semaphoreLeave(inputResponder->accessSemaphore);
}

//
// Mouse input
//

static void inputResponderMouseActionEvent(INPUT_RESPONDER* inputResponder, INPUT_MOUSE* inputMouse)
{
	semaphoreEnter(inputResponder->accessSemaphore);
	
	INPUT_DATA* inputData = inputResponder->stashedCommands;
	
	// 1. Fill mouse input data
	SF_ARRAY_PREPARE_NEXT(INPUT_MOUSE, inputData->mouseCommands, 32);
	INPUT_MOUSE* mouse = &SF_ARRAY_NEXT(inputData->mouseCommands);
	*mouse = *inputMouse;
	
	// 2. Fill input command data
	SF_ARRAY_PREPARE_NEXT(INPUT_COMMAND, inputData->commands, 32);
	INPUT_COMMAND* command = &SF_ARRAY_NEXT(inputData->commands);
	command->inputType = INPUT_COMMAND_TYPE_MOUSE;
	command->inputData = mouse;
	command->inputTime = systemGetCurrentTime(inputResponder->system);
	
	// 3. Stash command
	SF_ARRAY_STASH_NEXT(inputData->mouseCommands);
	SF_ARRAY_STASH_NEXT(inputData->commands);
	
	// 4. Delegate input event
	inputResponder->delegate(command, inputResponder->userInfo);
	
	semaphoreLeave(inputResponder->accessSemaphore);
}

void inputResponderMouseDown(INPUT_RESPONDER* inputResponder, MOUSE_KEY key, unsigned int otherKeyCode, float xPosition, float yPosition)
{
	assert(inputResponder);
	
	INPUT_MOUSE inputMouse =
	{
		.action = MOUSE_ACTION_DOWN,
		.key = key,
		.otherKeyCode = otherKeyCode,
		.xPosition = xPosition,
		.yPosition = yPosition,
		.xMove = 0.0f,
		.yMove = 0.0f,
		.xScroll = 0.0f,
		.yScroll = 0.0f
	};
	inputResponderMouseActionEvent(inputResponder, &inputMouse);
}

void inputResponderMouseUp(INPUT_RESPONDER* inputResponder, MOUSE_KEY key, unsigned int otherKeyCode, float xPosition, float yPosition)
{
	assert(inputResponder);
	
	INPUT_MOUSE inputMouse =
	{
		.action = MOUSE_ACTION_UP,
		.key = key,
		.otherKeyCode = otherKeyCode,
		.xPosition = xPosition,
		.yPosition = yPosition,
		.xMove = 0.0f,
		.yMove = 0.0f,
		.xScroll = 0.0f,
		.yScroll = 0.0f
	};
	inputResponderMouseActionEvent(inputResponder, &inputMouse);
}

void inputResponderMouseMove(INPUT_RESPONDER* inputResponder, MOUSE_KEY key, unsigned int otherKeyCode, float xPosition, float yPosition, float xMove, float yMove)
{
	assert(inputResponder);
	
	INPUT_MOUSE inputMouse =
	{
		.action = MOUSE_ACTION_MOVE,
		.key = key,
		.otherKeyCode = otherKeyCode,
		.xPosition = xPosition,
		.yPosition = yPosition,
		.xMove = xMove,
		.yMove = yMove,
		.xScroll = 0.0f,
		.yScroll = 0.0f
	};
	inputResponderMouseActionEvent(inputResponder, &inputMouse);
}

void inputResponderMouseScroll(INPUT_RESPONDER* inputResponder, MOUSE_KEY key, unsigned int otherKeyCode, float xPosition, float yPosition, float xScroll, float yScroll)
{
	assert(inputResponder);
	
	INPUT_MOUSE inputMouse =
	{
		.action = MOUSE_ACTION_SCROLL,
		.key = key,
		.otherKeyCode = otherKeyCode,
		.xPosition = xPosition,
		.yPosition = yPosition,
		.xMove = 0.0f,
		.yMove = 0.0f,
		.xScroll = xScroll,
		.yScroll = yScroll
	};
	inputResponderMouseActionEvent(inputResponder, &inputMouse);
}

//
// Touch input
//

static void inputResponderTouchAction(INPUT_RESPONDER* inputResponder, INPUT_TOUCH* touchInput)
{
	semaphoreEnter(inputResponder->accessSemaphore);
	
	INPUT_DATA* inputData = inputResponder->stashedCommands;
	
	// 1. Fill touch input data
	SF_ARRAY_PREPARE_NEXT(INPUT_TOUCH, inputData->touchCommands, 32);
	INPUT_TOUCH* dest = &SF_ARRAY_NEXT(inputData->touchCommands);
	*dest = *touchInput;
	
	// 2. Fill input command data
	SF_ARRAY_PREPARE_NEXT(INPUT_COMMAND, inputData->commands, 32);
	INPUT_COMMAND* command = &SF_ARRAY_NEXT(inputData->commands);
	command->inputType = INPUT_COMMAND_TYPE_TOUCH;
	command->inputData = dest;
	command->inputTime = systemGetCurrentTime(inputResponder->system);
	
	// 3. Stash command
	SF_ARRAY_STASH_NEXT(inputData->touchCommands);
	SF_ARRAY_STASH_NEXT(inputData->commands);
	
	// 4. Delegate input event
	inputResponder->delegate(command, inputResponder->userInfo);
	
	semaphoreLeave(inputResponder->accessSemaphore);
}

void inputResponderTouchDown(INPUT_RESPONDER* inputResponder, unsigned int touchIndex, vector2f position, float radius, float force)
{
	assert(inputResponder);
	
	INPUT_TOUCH touchInput =
	{
		.index = touchIndex,
		.action = TOUCH_ACTION_DOWN,
		.startPosition = position,
		.position = position,
		.delta = vector2fCreate(0.0f, 0.0f),
		.radius = radius,
		.force = force
	};
	inputResponderTouchAction(inputResponder, &touchInput);
}

void inputResponderTouchMove(INPUT_RESPONDER* inputResponder, unsigned int touchIndex, vector2f position, vector2f delta, float radius, float force)
{
	assert(inputResponder);
	
	INPUT_TOUCH touchInput =
	{
		.index = touchIndex,
		.action = TOUCH_ACTION_MOVE,
		.startPosition = position,
		.position = position,
		.delta = delta,
		.radius = radius,
		.force = force
	};
	inputResponderTouchAction(inputResponder, &touchInput);
}

void inputResponderTouchUp(INPUT_RESPONDER* inputResponder, unsigned int touchIndex, vector2f position)
{
	assert(inputResponder);
	
	INPUT_TOUCH touchInput =
	{
		.index = touchIndex,
		.action = TOUCH_ACTION_UP,
		.startPosition = vector2fCreate(0.0f, 0.0f),
		.position = position,
		.delta = vector2fCreate(0.0f, 0.0f),
		.radius = 0.0f,
		.force = 0.0f
	};
	inputResponderTouchAction(inputResponder, &touchInput);
}

void inputResponderTouchCancel(INPUT_RESPONDER* inputResponder, unsigned int touchIndex)
{
	assert(inputResponder);
	
	INPUT_TOUCH touchInput =
	{
		.index = touchIndex,
		.action = TOUCH_ACTION_CANCEL,
		.startPosition = vector2fCreate(0.0f, 0.0f),
		.position = vector2fCreate(0.0f, 0.0f),
		.delta = vector2fCreate(0.0f, 0.0f),
		.radius = 0.0f,
		.force = 0.0f
	};
	inputResponderTouchAction(inputResponder, &touchInput);
}

//
// Interface implementation
//

//
// Tracking user input
//

//
// Tracking keyboard input
//

TRACKING_KEYBOARD_BUTTON* inputResponderTrackKeyboardButton(INPUT_RESPONDER* inputResponder, KEY_BUTTON_TYPE type, unsigned int keyCode)
{
	assert(inputResponder);
	
	for (unsigned int i = 0; i < SF_ARRAY_LEN(inputResponder->trackingKeyboardButtons); i++)
	{
		TRACKING_KEYBOARD_BUTTON* currentButton = inputResponder->trackingKeyboardButtons[i];
		if (currentButton->type == type && currentButton->keyCode == keyCode)
		{
			return currentButton;
		}
	}
	
	TRACKING_KEYBOARD_BUTTON* button = trackingKeyboardButtonCreate(type, keyCode);
	SF_ARRAY_PREPARE_NEXT(TRACKING_KEYBOARD_BUTTON*, inputResponder->trackingKeyboardButtons, 128);
	SF_ARRAY_STASH_NEXT(inputResponder->trackingKeyboardButtons);
	SF_ARRAY_LAST(inputResponder->trackingKeyboardButtons) = button;
	
	return button;
}

//
// Tracking mouse input
//

float inputResponderGetMouseX(INPUT_RESPONDER* inputResponder)
{
	assert(inputResponder);
	return inputResponder->mouseX;
}

float inputResponderGetMouseY(INPUT_RESPONDER* inputResponder)
{
	assert(inputResponder);
	return inputResponder->mouseY;
}

vector2f inputResponderGetMouseMove(INPUT_RESPONDER* inputResponder)
{
	assert(inputResponder);
	return vector2fCreate(inputResponder->mouseMoveX, inputResponder->mouseMoveY);
}

float inputResponderGetMouseMoveX(INPUT_RESPONDER* inputResponder)
{
	assert(inputResponder);
	return inputResponder->mouseMoveX;
}

float inputResponderGetMouseMoveY(INPUT_RESPONDER* inputResponder)
{
	assert(inputResponder);
	return inputResponder->mouseMoveY;
}


float inputResponderGetMouseScrollX(INPUT_RESPONDER* inputResponder)
{
	assert(inputResponder);
	return inputResponder->mouseScrollX;
}

float inputResponderGetMouseScrollY(INPUT_RESPONDER* inputResponder)
{
	assert(inputResponder);
	return inputResponder->mouseScrollY;
}
