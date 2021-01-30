//
//  buffer_writer.c
//  Foundation
//
//  Created by Евгений Лютц on 01.01.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

BUFFER_WRITER* bufferWriterCreate(BUFFER* buffer, unsigned int sizeIncrement)
{
	assert(buffer);
	
	BUFFER_WRITER* writer = malloc(sizeof(BUFFER_WRITER));
	writer->buffer = buffer;
	writer->editorPosition = 0;
	writer->capacityIncrement = sizeIncrement;
	writer->buffer->numReferences++;
	return writer;
}

void bufferWriterRelease(BUFFER_WRITER* bufferWriter)
{
	assert(bufferWriter);
	
	bufferWriter->buffer->numReferences--;
	debug_memset(bufferWriter, 0, sizeof(BUFFER_WRITER));
	free(bufferWriter);
}


static inline void _bufferReader_requestMemory(BUFFER_WRITER* writer, unsigned long length)
{
	if (writer->buffer->length + length > writer->buffer->capacity)
	{
#if DEBUG
		unsigned long oldCapacity = writer->buffer->capacity;
#endif
		
		const unsigned long increment = length > writer->capacityIncrement ? length : writer->capacityIncrement;
		const unsigned long capacity = writer->buffer->capacity + increment;
		writer->buffer->length = capacity;
		writer->buffer->data = realloc(writer->buffer->data, capacity);
		assert(writer->buffer->data);
		
#if DEBUG
		memset(&(writer->buffer->data[oldCapacity]), 0, writer->buffer->length - oldCapacity);
#endif
	}
}

char* bufferRequestDataToWrite(BUFFER_WRITER* buffer, unsigned long length)
{
	assert(buffer);
	
	_bufferReader_requestMemory(buffer, length);
	char* data = &(buffer->buffer->data[buffer->editorPosition]);
#if DEBUG
	memset(data, 0, length);
#endif
	
	buffer->buffer->length += length;
	buffer->editorPosition += length;
	
	return data;
}


void bufferWriteData(BUFFER_WRITER* buffer, const char* data, unsigned long length)
{
	assert(buffer);
	
	_bufferReader_requestMemory(buffer, length);
	memcpy(&(buffer->buffer->data[buffer->editorPosition]), data, length);
	buffer->buffer->length += length;
	buffer->editorPosition += length;
}

void bufferWriteInt8(BUFFER_WRITER* buffer, char data) {
	bufferWriteData(buffer, (char*)&data, sizeof(int8_t));
}

void bufferWriteIntU8(BUFFER_WRITER* buffer, unsigned char data) {
	bufferWriteData(buffer, (char*)&data, sizeof(uint8_t));
}

void bufferWriteInt16(BUFFER_WRITER* buffer, short data) {
	bufferWriteData(buffer, (char*)&data, sizeof(int16_t));
}

void bufferWriteIntU16(BUFFER_WRITER* buffer, unsigned short data) {
	bufferWriteData(buffer, (char*)&data, sizeof(uint16_t));
}

void bufferWriteInt32(BUFFER_WRITER* buffer, int data) {
	bufferWriteData(buffer, (char*)&data, sizeof(int32_t));
}

void bufferWriteIntU32(BUFFER_WRITER* buffer, unsigned int data) {
	bufferWriteData(buffer, (char*)&data, sizeof(uint32_t));
}

void bufferWriteInt64(BUFFER_WRITER* buffer, long data) {
	bufferWriteData(buffer, (char*)&data, sizeof(int64_t));
}

void bufferWriteIntU64(BUFFER_WRITER* buffer, unsigned long data) {
	bufferWriteData(buffer, (char*)&data, sizeof(uint64_t));
}
