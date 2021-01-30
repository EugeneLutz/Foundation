//
//  system_io_functions.h
//  Foundation
//
//  Created by Евгений Лютц on 20.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef system_io_functions_h
#define system_io_functions_h

#include "foundation.h"

/*!
 @abstract
 Returns absolute file path to the resource located in applications bundle.
 */
typedef void (* SISTEM_IO_GET_FILE_PATH_WITH_NAME_AND_TYPE_FUNC)(SYSTEM* system, STRING* outPath, const char* name, const char* extension, EXECUTE_RESULT* executeResult);

/*!
 @abstract
 Delegate function to open a file by given path with specified mode.
 
 @discussion
 This function should return a number that identifies created file. Later, the engine will use this identifier to work with file. The engine calls this function to open a file.
 
 @param path
 Path to the file.
 
 @param fileMode
 Mode in which file will be read.
 
 @param userInfo
 Specified by user custom data that is sent in further calls.
 
 @param executeResult
 Result of function execution.
 
 @result
 User-defined file identifier.
*/
typedef void* (* FILE_OPEN_READ_FUNC)(const char* path, FILE_MODE fileMode, void* userInfo, EXECUTE_RESULT* executeResult);

//typedef void* (* FILE_OPEN_WRITE_FUNC)(const char* path, FILE_MODE fileMode, int append, void* userInfo, EXECUTE_RESULT* executeResult);

/*!
 @abstract
 Close file delegate function.
 @discussion
 Delegate function to close a file opened earlier with specified by user FILE_OPEN_READ_FUNC functon. The engine calls this function to close a file.
 */
typedef void (* FILE_CLOSE_FUNC)(void* fileId, void* userInfo, EXECUTE_RESULT* executeResult);

typedef unsigned long (* FILE_GET_SIZE_FUNC)(void* fileId, void* userInfo, EXECUTE_RESULT* executeResult);

typedef void (* FILE_SET_POSITION_FUNC)(void* fileId, unsigned long position, void* userInfo, EXECUTE_RESULT* executeResult);

typedef unsigned int (* FILE_READ_DATA_FUNC)(void* fileId, void* destination, unsigned long dataSize, void* userInfo, EXECUTE_RESULT* executeResult);

#endif /* system_io_functions_h */
