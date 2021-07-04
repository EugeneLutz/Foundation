//
//  input_responder_public.h
//  Foundation
//
//  Created by Евгений Лютц on 20.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef input_responder_public_h
#define input_responder_public_h

#include "foundation.h"

/**
 * @abstract
 * Create an input responder.
 *
 * @discussion
 * You create this object to accept and process user input data.
 *
 * @note
 * After creating input responder, release it with @b inputResponderRelease function when it will not be needed.
 *
 * @param delegate
 * Delegate function used to process user input data.
 *
 * @param userInfo
 * Custom data specified by user. It passes as last parameter of @b delegate function.
 *
 * @param system
 * System interface provided by user.
 *
 * @param executeResult
 * Execution result of this function.
 *
 * @returns
 * A newly created input responder if succeeded, otherwise @e NULL. @b executeResult contains information that may help to solve problem if @e NULL is returned.
 *
 * @seealso INPUT_RESPONDER SYSTEM
 */
INPUT_RESPONDER* inputResponderCreate(INPUT_RESPONDER_DELEGATE_FUNC delegate, void* userInfo, SYSTEM* system, EXECUTE_RESULT* executeResult);
void inputResponderRelease(INPUT_RESPONDER* inputResponder);

// MARK: Stashing input data

/**
 @abstract Resets previously accumulated commands and swaps to new collected ones.
 @discussion TODO: I need to explain this.
 */
void inputResponderResetInput(INPUT_RESPONDER* inputResponder);
unsigned int inputResponderGetNumAccumulatedCommands(INPUT_RESPONDER* inputResponder);
INPUT_COMMAND* inputResponderGetAccumulatedCommand(INPUT_RESPONDER* inputResponder, unsigned int commandIndex);

// MARK: Keyboard input

void inputResponderKeyboardAction(INPUT_RESPONDER* inputResponder, KEY_ACTION action, KEY_BUTTON_TYPE buttonType, unsigned int buttonKeyCode);

// MARK: Mouse input

void inputResponderMouseDown(INPUT_RESPONDER* inputResponder, MOUSE_KEY key, unsigned int otherKeyCode, float xPosition, float yPosition);
void inputResponderMouseUp(INPUT_RESPONDER* inputResponder, MOUSE_KEY key, unsigned int otherKeyCode, float xPosition, float yPosition);
void inputResponderMouseMove(INPUT_RESPONDER* inputResponder, MOUSE_KEY key, unsigned int otherKeyCode, float xPosition, float yPosition, float xMove, float yMove);
void inputResponderMouseScroll(INPUT_RESPONDER* inputResponder, MOUSE_KEY key, unsigned int otherKeyCode, float xPosition, float yPosition, float xScroll, float yScroll);

// MARK: Touch input

void inputResponderTouchDown(INPUT_RESPONDER* inputResponder, unsigned int touchIndex, vector2f position, float radius, float force);
void inputResponderTouchMove(INPUT_RESPONDER* inputResponder, unsigned int touchIndex, vector2f position, vector2f delta, float radius, float force);
void inputResponderTouchUp(INPUT_RESPONDER* inputResponder, unsigned int touchIndex, vector2f position);
void inputResponderTouchCancel(INPUT_RESPONDER* inputResponder, unsigned int touchIndex);


// MARK: - Tracking user input

TRACKING_KEYBOARD_BUTTON* inputResponderTrackKeyboardButton(INPUT_RESPONDER* inputResponder, KEY_BUTTON_TYPE type, unsigned int keyCode);
//void* inputResponderTrackKeyboardInput(INPUT_RESPONDER* inputResponder);

// MARK: Track mouse input

float inputResponderGetMouseX(INPUT_RESPONDER* inputResponder);
float inputResponderGetMouseY(INPUT_RESPONDER* inputResponder);

vector2f inputResponderGetMouseMove(INPUT_RESPONDER* inputResponder);
float inputResponderGetMouseMoveX(INPUT_RESPONDER* inputResponder);
float inputResponderGetMouseMoveY(INPUT_RESPONDER* inputResponder);

float inputResponderGetMouseScrollX(INPUT_RESPONDER* inputResponder);
float inputResponderGetMouseScrollY(INPUT_RESPONDER* inputResponder);

#endif /* input_responder_public_h */
