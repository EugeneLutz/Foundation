//
//  io_apple.m
//  Foundation
//
//  Created by Евгений Лютц on 24.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"
#import <Foundation/Foundation.h>

static void _apple_getPathForResourceWithNameAndType(SYSTEM* system, STRING* outPath, const char* name, const char* type, EXECUTE_RESULT* executeResult)
{
	NSString* resourceName = [NSString stringWithUTF8String:name];
	NSString* typeName = [NSString stringWithUTF8String:type];
	NSString* resourcePath = [NSBundle.mainBundle pathForResource:resourceName ofType:typeName];
	if (!resourcePath) {
		executeResultSetFailed(executeResult, "Cannot find file with given path.");
		return;
	}
	
	stringSetData(outPath, resourcePath.UTF8String);
	executeResultSetSucceeded(executeResult);
}

static void* _openReadFile(const char* path, FILE_MODE fileMode, void* userInfo, EXECUTE_RESULT* executeResult)
{
	//FILE* file = fopen(path, fileMode == FILE_MODE_TEXT ? "r" : "rb");
	FILE* file = fopen(path, "r");
	if (!file)
	{
		executeResultSetFailed(executeResult, "Cannot open file");
		return NULL;
	}
	
	return file;
}

static void _closeFile(void* fileId, void* userInfo, EXECUTE_RESULT* executeResult)
{
	assert(fileId);
	
	FILE* file = fileId;
	fclose(file);
	
	executeResultSetSucceeded(executeResult);
}

static unsigned long _getFileSize(void* fileId, void* userInfo, EXECUTE_RESULT* executeResult)
{
	assert(fileId);
	
	FILE* file = fileId;
	
	long position = ftell(file);
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, position, SEEK_SET);
	
	executeResultSetSucceeded(executeResult);
	return (unsigned int)size;
}

static void _setFilePosition(void* fileId, unsigned long position, void* userInfo, EXECUTE_RESULT* executeResult)
{
	fseek(fileId, position, SEEK_SET);
	executeResultSetSucceeded(executeResult);
}

static unsigned int _readDataFunc(void* fileId, void* destination, unsigned long dataSize, void* userInfo, EXECUTE_RESULT* executeResult)
{
	FILE* file = fileId;
	
	unsigned int readResult = (unsigned int)fread(destination, dataSize, 1, file);
	
	executeResultSetSucceeded(executeResult);
	return readResult;
}

void systemInitIOFunctionsApple(SYSTEM* system)
{
	assert(system);
	
	system->getPathForResourceWithNameAndTypeFunc = _apple_getPathForResourceWithNameAndType;
	system->fileOpenReadFunc = _openReadFile;
	system->fileCloseFunc = _closeFile;
	system->fileGetSizeFunc = _getFileSize;
	system->fileSetPositionFunc = _setFilePosition;
	system->fileReadDataFunc = _readDataFunc;
}
