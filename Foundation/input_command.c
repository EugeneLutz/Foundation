//
//  input_command.c
//  Foundation
//
//  Created by Евгений Лютц on 23.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

INPUT_COMMAND_TYPE inputCommandGetInputType(INPUT_COMMAND* inputCommand)
{
	assert(inputCommand != NULL);
	return inputCommand->inputType;
}

INPUT_KEYBOARD* inputCommandGetKeyboardInput(INPUT_COMMAND* inputCommand)
{
	assert(inputCommand != NULL);
	assert(inputCommand->inputType == INPUT_COMMAND_TYPE_KEYBOARD);
	return (INPUT_KEYBOARD*)(inputCommand->inputData);
}

INPUT_MOUSE* inputCommandGetMouseInput(INPUT_COMMAND* inputCommand)
{
	assert(inputCommand != NULL);
	assert(inputCommand->inputType == INPUT_COMMAND_TYPE_MOUSE);
	return (INPUT_MOUSE*)(inputCommand->inputData);
}

INPUT_TOUCH* inputCommandGetTouchInput(INPUT_COMMAND* inputCommand)
{
	assert(inputCommand != NULL);
	assert(inputCommand->inputType == INPUT_COMMAND_TYPE_TOUCH);
	return (INPUT_TOUCH*)(inputCommand->inputData);
}

double inputCommandGetInputTime(INPUT_COMMAND* inputCommand)
{
	assert(inputCommand != NULL);
	return inputCommand->inputTime;
}
