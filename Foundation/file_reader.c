//
//  file_reader.c
//  Foundation
//
//  Created by Евгений Лютц on 25.12.2019.
//  Copyright © 2019 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

FILE_READER* systemOpenFileReader(SYSTEM* system, const char* filePath, FILE_MODE mode, EXECUTE_RESULT* executeResult)
{
	assert(system);
	assert(filePath);
	
	FILE_READER* reader = malloc(sizeof(FILE_READER));
	reader->system = system;
	
	reader->fileId = (*reader->system->fileOpenReadFunc)(filePath, mode, reader->system->userInfo, executeResult);
	if (executeResultIsFailed(executeResult))
	{
		free(reader);
		return NULL;
	}
	
	reader->size = (*reader->system->fileGetSizeFunc)(reader->fileId, reader->system->userInfo, executeResult);
	if (executeResultIsFailed(executeResult))
	{
		(*reader->system->fileCloseFunc)(reader->fileId, reader->system->userInfo, executeResult);
		free(reader);
		return NULL;
	}
	
	reader->position = 0;
	reader->buffer = malloc(sizeof(unsigned char) * reader->size);
	if (!reader->buffer)
	{
		(*reader->system->fileCloseFunc)(reader->fileId, reader->system->userInfo, executeResult);
		free(reader);
		
		executeResultSetFailed(executeResult, "Cannot allocate memory for reading a file.");
		return NULL;
	}
	
	(*reader->system->fileReadDataFunc)(reader->fileId, reader->buffer, reader->size, reader->system->userInfo, executeResult);
	if (executeResultIsFailed(executeResult))
	{
		free(reader->buffer);
		(*reader->system->fileCloseFunc)(reader->fileId, reader->system->userInfo, executeResult);
		free(reader);
		return NULL;
	}
	
	fileReaderSetPosition(reader, 0, executeResult);
	if (executeResultIsFailed(executeResult)) {
		fileReaderClose(reader, NULL);
		return NULL;
	}
	
	executeResultSetSucceeded(executeResult);
	return reader;
}

void fileReaderClose(FILE_READER* reader, EXECUTE_RESULT* executeResult)
{
	assert(reader);
	
	free(reader->buffer);
	(*reader->system->fileCloseFunc)(reader->fileId, reader->system->userInfo, executeResult);
	if (executeResultIsFailed(executeResult))
	{
		free(reader);
		return;
	}
	free(reader);
	
	executeResultSetSucceeded(executeResult);
}


void fileReaderSetPosition(FILE_READER* reader, unsigned long position, EXECUTE_RESULT* executeResult)
{
	if (!reader) {
		executeResultSetFailed(executeResult, "File reader is not specified.");
		return;
	}
	
	if (position > reader->size) {
		executeResultSetFailed(executeResult, "Specified position is out of file's size.");
		return;
	}
	
	reader->system->fileSetPositionFunc(reader->fileId, position, reader->system->userInfo, executeResult);
}

void fileReaderReadToBuffer(FILE_READER* reader, BUFFER* buffer, unsigned long size, EXECUTE_RESULT* executeResult)
{
	if (size == 0) {
		executeResultSetSucceeded(executeResult);
		return;
	}
	
	if (!reader) {
		executeResultSetFailed(executeResult, "File reader is not specified.");
		return;
	}
	
	if (!buffer) {
		executeResultSetFailed(executeResult, "Buffer to write data is not specified.");
		return;
	}
	
	bufferRequestSize(buffer, size);
	(*reader->system->fileReadDataFunc)(reader->fileId, buffer->data, size, reader->system->userInfo, executeResult);
	buffer->length = size;
}


#define reader_next(reader) reader->position++

void fileReaderSkipLine(FILE_READER* reader, EXECUTE_RESULT* executeResult)
{
	if (reader->position == reader->size)
	{
		executeResultSetFailed(executeResult, "Nothing to read.");
		return;
	}
	
	while (reader->buffer[reader->position] != '\n')
	{
		reader->position++;
		if (reader->position == reader->size)
		{
			executeResultSetFailed(executeResult, "There is no end of string.");
			return;
		}
	}
	reader->position++;
	
	executeResultSetSucceeded(executeResult);
}

void fileReaderReadString(STRING* string, FILE_READER* reader, EXECUTE_RESULT* executeResult)
{
	assert(reader);
	
	unsigned long start = reader->position;
	unsigned long end = start;
	if (end >= reader->size)
	{
		executeResultSetFailed(executeResult, "Nothing to read.");
		return;
	}
	
	while (reader->buffer[end] != '\n')
	{
		reader_next(reader);
		end++;
		
		if (end == reader->size)
		{
			executeResultSetFailed(executeResult, "There is no end of string.");
			return;
		}
	}
	reader_next(reader);
	
	stringSetDataWithSubstring(string, (char*)(reader->buffer), start, end - start);
	executeResultSetSucceeded(executeResult);
}

void fileReaderReadAllContentsToString(STRING* outString, FILE_READER* reader, EXECUTE_RESULT* executeResult)
{
	assert(outString);
	assert(reader);
	
	stringSetDataWithLength(outString, (char*)reader->buffer, reader->size - 1);
	executeResultSetSucceeded(executeResult);
}

#define find_string(reader, dataName, defaultValue)\
	assert(reader);\
	unsigned long start = reader->position;\
	unsigned long end = start;\
	if (end >= reader->size) {\
		executeResultSetFailed(executeResult, "Nothing to read.");\
		return defaultValue;\
	}\
	while (reader->buffer[end] != '\n') {\
		reader_next(reader);\
		end++;\
		if (end == reader->size) {\
			executeResultSetFailed(executeResult, "There is no end of string.");\
			return defaultValue;\
		}\
	}\
	reader_next(reader);\
	const char* dataName = (char*)(reader->buffer) + sizeof(char) * (start);

#define return_result \
executeResultSetSucceeded(executeResult);\
return result

double fileReaderReadStringAsDouble(FILE_READER* reader, EXECUTE_RESULT* executeResult)
{
	find_string(reader, data, 0.0);
	double result = (double)strtod(data, NULL);
	return_result;
}

float fileReaderReadStringAsFloat(FILE_READER* reader, EXECUTE_RESULT* executeResult)
{
	find_string(reader, data, 0.0f);
	float result = (float)strtof(data, NULL);
	return_result;
}

unsigned int fileReaderReadStringAsUInt(FILE_READER* reader, EXECUTE_RESULT* executeResult)
{
	find_string(reader, data, 0);
	unsigned int result = (unsigned int)strtoul(data, NULL, 10);
	return_result;
}

int fileReaderReadStringAsInt(FILE_READER* reader, EXECUTE_RESULT* executeResult)
{
	find_string(reader, data, 0);
	int result = (int)strtol(data, NULL, 10);
	return_result;
}
