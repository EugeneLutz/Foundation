//
//  input_command.h
//  Foundation
//
//  Created by Евгений Лютц on 20.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef input_command_h
#define input_command_h

#include "private_interface.h"

/**
 * @abstract User input information
 * @discussion When user... what?
 */
typedef struct INPUT_COMMAND
{
	INPUT_COMMAND_TYPE inputType;
	void* inputData;
	double inputTime;
}
INPUT_COMMAND;

#endif /* input_command_h */
