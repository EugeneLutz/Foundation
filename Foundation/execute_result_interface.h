//
//  execute_result_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 24.12.2019.
//  Copyright © 2019 Eugene Lutz. All rights reserved.
//

#ifndef execute_result_interface_h
#define execute_result_interface_h

#include "foundation.h"

EXECUTE_RESULT* executeResultCreate(void);
void executeResultRelease(EXECUTE_RESULT* executeResult);

int executeResultIsSucceeded(EXECUTE_RESULT* executeResult);
int executeResultIsFailed(EXECUTE_RESULT* executeResult);
int executeResultGetCode(EXECUTE_RESULT* executeResult);
const char* executeResultGetMessage(EXECUTE_RESULT* executeResult);
const char* executeResultGetComment(EXECUTE_RESULT* executeResult);

void executeResultSetSucceeded(EXECUTE_RESULT* executeResult);
void executeResultSetSucceededWithWarning(EXECUTE_RESULT* executeResult, int warningCode, const char* warningMessage);
void executeResultSetFailed(EXECUTE_RESULT* executeResult, const char* message);
void executeResultSetFailedWithCode(EXECUTE_RESULT* executeResult, int code, const char* message, const char* comment);

void executeResultCopy(EXECUTE_RESULT* executeResult, EXECUTE_RESULT* source);

#endif /* execute_result_interface_h */
