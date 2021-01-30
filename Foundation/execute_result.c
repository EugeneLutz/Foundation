//
//  execute_result.c
//  Foundation
//
//  Created by Евгений Лютц on 24.12.2019.
//  Copyright © 2019 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

EXECUTE_RESULT* executeResultCreate(void)
{
	EXECUTE_RESULT* executeResult = malloc(sizeof(EXECUTE_RESULT));
	memset(executeResult, 0, sizeof(EXECUTE_RESULT));
	return executeResult;
}

void executeResultRelease(EXECUTE_RESULT* executeResult)
{
	assert(executeResult != NULL);
	free(executeResult);
}


int executeResultIsSucceeded(EXECUTE_RESULT* executeResult)
{
	if (!executeResult)
	{
		return 1;
	}
	
	return executeResult->succeeded;
}

int executeResultIsFailed(EXECUTE_RESULT* executeResult)
{
	if (!executeResult)
	{
		return 0;
	}
	
	return executeResult->succeeded == 0;
}

int executeResultGetCode(EXECUTE_RESULT* executeResult)
{
	assert(executeResult != NULL);
	return executeResult->code;
}

const char* executeResultGetMessage(EXECUTE_RESULT* executeResult)
{
	assert(executeResult != NULL);
	return executeResult->message;
}

const char* executeResultGetComment(EXECUTE_RESULT* executeResult)
{
	assert(executeResult != NULL);
	return executeResult->comment;
}


void executeResultSetSucceeded(EXECUTE_RESULT* executeResult)
{
	if (!executeResult)
	{
		return;
	}
	
	executeResult->succeeded = 1;
	executeResult->code = 0;
	executeResult->message[0] = 0;
	executeResult->comment[0] = 0;
}

void executeResultSetSucceededWithWarning(EXECUTE_RESULT* executeResult, int warningCode, const char* warningMessage)
{
	if (!executeResult)
	{
		return;
	}
	
	executeResult->succeeded = 1;
	executeResult->message[0] = 0;
	
	executeResult->code = warningCode;
	strcpy(executeResult->comment, warningMessage);
}

void executeResultSetFailed(EXECUTE_RESULT* executeResult, const char* message)
{
	if (!executeResult)
	{
		return;
	}
	
	executeResult->succeeded = 0;
	strcpy(executeResult->message, message);
	
	executeResult->code = 0;
	executeResult->comment[0] = 0;
}

void executeResultSetFailedWithCode(EXECUTE_RESULT* executeResult, int code, const char* message, const char* comment)
{
	if (!executeResult)
	{
		return;
	}
	
	executeResult->succeeded = 0;
	executeResult->code = code;
	strcpy(executeResult->message, message);
	strcpy(executeResult->comment, comment);
}


void executeResultCopy(EXECUTE_RESULT* executeResult, EXECUTE_RESULT* source)
{
	if (!executeResult || !source)
	{
		return;
	}
	
	executeResult->succeeded = source->succeeded;
	executeResult->code = source->code;
	strcpy(executeResult->message, source->message);
	strcpy(executeResult->comment, source->comment);
}
