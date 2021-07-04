//
//  buffer_reader.c
//  Foundation
//
//  Created by Евгений Лютц on 01.01.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

BUFFER_READER* bufferReaderCreate(BUFFER* buffer)
{
	assert(buffer);
	
	BUFFER_READER* reader = malloc(sizeof(BUFFER_READER));
	reader->buffer = buffer;
	reader->editorPosition = 0;
//	reader->buffer->numReferences++;
	return reader;
}

void bufferReaderRelease(BUFFER_READER* bufferReader)
{
	assert(bufferReader);
	
//	bufferReader->buffer->numReferences--;
	debug_memset(bufferReader, 0, sizeof(BUFFER_READER));
	free(bufferReader);
}


void bufferReaderSetEditorPosition(BUFFER_READER* reader, unsigned long position)
{
	assert(reader);
	assert(position <= reader->buffer->length);
	reader->editorPosition = position;
}


char* bufferReaderRequestDataToRead(BUFFER_READER* reader, unsigned long length, EXECUTE_RESULT* executeResult)
{
	assert(reader);
	if (reader->editorPosition + length > reader->buffer->length) {
		char message[256];
		sprintf(message, "Requested too much data to retrieve. %ld bytes were requested when %ld bytes were available (buffer length: %ld, editor position: %ld).", length, reader->buffer->length - reader->editorPosition, reader->buffer->length, reader->editorPosition);
		executeResultSetFailed(executeResult, message);
		return NULL;
	}
	
	char* data = reader->buffer->data + reader->editorPosition;
	reader->editorPosition += length;
	return data;
}

static inline void _bufferReader_readRawData(BUFFER_READER* reader, char* data, unsigned long length, EXECUTE_RESULT* executeResult)
{
	assert(reader);
	assert(data);
	
	if (length == 0) {
		return;
	}
	
	if (reader->editorPosition == reader->buffer->length) {
		executeResultSetFailed(executeResult, "The end of buffer is reached.");
		return;
	}
	else if (reader->editorPosition + length > reader->buffer->length) {
		char message[256];
		sprintf(message, "Requested too much data to retrieve. %ld bytes were requested when %ld bytes were available (buffer length: %ld, editor position: %ld).", length, reader->buffer->length - reader->editorPosition, reader->buffer->length, reader->editorPosition);
		executeResultSetFailed(executeResult, message);
		return;
	 }
	
	memcpy(data, &(reader->buffer->data[reader->editorPosition]), length);
	reader->editorPosition += length;
	
	executeResultSetSucceeded(executeResult);
}

char bufferReaderReadInt8(BUFFER_READER* reader, EXECUTE_RESULT* executeResult) {
	int8_t data = 0;
	_bufferReader_readRawData(reader, (char*)&data, sizeof(int8_t), executeResult);
	return data;
}

unsigned char bufferReaderReadUInt8(BUFFER_READER* reader, EXECUTE_RESULT* executeResult) {
	uint8_t data = 0;
	_bufferReader_readRawData(reader, (char*)&data, sizeof(uint8_t), executeResult);
	return data;
}

short bufferReaderReadInt16(BUFFER_READER* reader, EXECUTE_RESULT* executeResult) {
	int16_t data = 0;
	_bufferReader_readRawData(reader, (char*)&data, sizeof(int16_t), executeResult);
	return data;
}

unsigned short bufferReaderReadUInt16(BUFFER_READER* reader, EXECUTE_RESULT* executeResult) {
	uint16_t data = 0;
	_bufferReader_readRawData(reader, (char*)&data, sizeof(uint16_t), executeResult);
	return data;
}

int bufferReaderReadInt32(BUFFER_READER* reader, EXECUTE_RESULT* executeResult) {
	int32_t data = 0;
	_bufferReader_readRawData(reader, (char*)&data, sizeof(int32_t), executeResult);
	return data;
}

unsigned int bufferReaderReadUInt32(BUFFER_READER* reader, EXECUTE_RESULT* executeResult) {
	uint32_t data = 0;
	_bufferReader_readRawData(reader, (char*)&data, sizeof(uint32_t), executeResult);
	return data;
}

long bufferReaderReadInt64(BUFFER_READER* reader, EXECUTE_RESULT* executeResult) {
	int64_t data = 0;
	_bufferReader_readRawData(reader, (char*)&data, sizeof(int64_t), executeResult);
	return data;
}

unsigned long bufferReaderReadUInt64(BUFFER_READER* reader, EXECUTE_RESULT* executeResult) {
	uint64_t data = 0;
	_bufferReader_readRawData(reader, (char*)&data, sizeof(uint64_t), executeResult);
	return data;
}
