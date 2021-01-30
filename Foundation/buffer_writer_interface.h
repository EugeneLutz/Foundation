//
//  buffer_writer_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 01.01.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#ifndef buffer_writer_interface_h
#define buffer_writer_interface_h

#include "foundation.h"

BUFFER_WRITER* bufferWriterCreate(BUFFER* buffer, unsigned int capacityIncrement);
void bufferWriterRelease(BUFFER_WRITER* bufferWriter);

char* bufferWriterRequestDataToWrite(BUFFER_WRITER* writer, unsigned long length);
void bufferWriterWriteData(BUFFER_WRITER* writer, const char* data, unsigned long length);
void bufferWriterWriteInt8(BUFFER_WRITER* writer, char data);
void bufferWriterWriteIntU8(BUFFER_WRITER* writer, unsigned char data);
void bufferWriterWriteInt16(BUFFER_WRITER* writer, short data);
void bufferWriterWriteIntU16(BUFFER_WRITER* writer, unsigned short data);
void bufferWriterWriteInt32(BUFFER_WRITER* writer, int data);
void bufferWriterWriteIntU32(BUFFER_WRITER* writer, unsigned int data);
void bufferWriterWriteInt64(BUFFER_WRITER* writer, long data);
void bufferWriterWriteIntU64(BUFFER_WRITER* writer, unsigned long data);

#endif /* buffer_writer_interface_h */
