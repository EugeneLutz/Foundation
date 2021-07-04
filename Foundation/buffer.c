//
//  buffer.c
//  Foundation
//
//  Created by Евгений Лютц on 01.01.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

// MARK: - Private interface

void bufferInitialize(BUFFER* buffer, unsigned long capacity)
{
	assert(buffer);
	buffer->referenced = 0;
	buffer->capacity = capacity;
	buffer->length = 0;
	buffer->data = malloc(sizeof(char) * capacity);
	debug_memset(buffer->data, 0, sizeof(char) * capacity);
}

void bufferDeinitialize(BUFFER* buffer)
{
	assert(buffer);
	assert(buffer->data);
	
	if (!buffer->referenced)
	{
		free(buffer->data);
		debug_memset(buffer, 0, sizeof(BUFFER));
	}
}

void bufferRequestSize(BUFFER* buffer, unsigned long length)
{
	assert(buffer);
	assert(!buffer->referenced);
	
	if (buffer->capacity < length)
	{
		buffer->capacity = length;
		buffer->data = realloc(buffer->data, sizeof(char) * buffer->capacity);
		assert(buffer->data);
	}
}

// MARK: - Public interface

BUFFER* bufferCreate(unsigned long length)
{
	BUFFER* buffer = malloc(sizeof(BUFFER));
	bufferInitialize(buffer, length);
	
	return buffer;
}

BUFFER* bufferCreateReferenced(char* data, unsigned long length)
{
	BUFFER* buffer = malloc(sizeof(BUFFER));
	buffer->referenced = 1;
	buffer->capacity = length;
	buffer->length = length;
	buffer->data = data;
	
	return buffer;
}

BUFFER* bufferCreateFromContentsOfFile(SYSTEM* system, const char* path, EXECUTE_RESULT* executeResult)
{
	assert(system);
	assert(path);
	
	// TODO: test this code
//	assert(0);
	
	FILE_READER* reader = systemOpenFileReader(system, path, FILE_MODE_BINARY, executeResult);
	if (reader == NULL || executeResultIsFailed(executeResult))
	{
		return NULL;
	}
	
	BUFFER* buffer = bufferCreate(reader->size);
	fileReaderReadToBuffer(reader, buffer, reader->size, executeResult);
	if (executeResultIsFailed(executeResult))
	{
		bufferRelease(buffer);
		fileReaderClose(reader, NULL);
		return NULL;
	}
	
	fileReaderClose(reader, executeResult);
	if (executeResultIsFailed(executeResult))
	{
		bufferRelease(buffer);
		return NULL;
	}
	
	return buffer;
}

BUFFER* bufferCreateFromContentsOfResourceFile(SYSTEM* system, const char* name, const char* type, EXECUTE_RESULT* executeResult)
{
	assert(system);
	assert(name);
	assert(type);
	
	STRING path;
	stringInitializeWithUTF8String(&path, NULL);
	systemGetPathForResourceWithName(system, &path, name, type, executeResult);
	if (executeResultIsFailed(executeResult))
	{
		stringDeinitialize(&path);
		return NULL;
	}
	
	BUFFER* buffer = bufferCreateFromContentsOfFile(system, path.data, executeResult);
	stringDeinitialize(&path);
	return buffer;
}

void bufferRelease(BUFFER* buffer)
{
	assert(buffer);
	
	bufferDeinitialize(buffer);
	free(buffer);
}


unsigned long bufferGetLength(BUFFER* buffer)
{
	assert(buffer);
	return buffer->length;
}
