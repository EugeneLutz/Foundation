//
//  buffer_reader_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 01.01.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#ifndef buffer_reader_interface_h
#define buffer_reader_interface_h

#include "foundation.h"

BUFFER_READER* bufferReaderCreate(BUFFER* buffer);
void bufferReaderRelease(BUFFER_READER* bufferReader);

void bufferReaderSetEditorPosition(BUFFER_READER* reader, unsigned long position);

char* bufferReaderRequestDataToRead(BUFFER_READER* reader, unsigned long length, EXECUTE_RESULT* executeResult);
char bufferReaderReadInt8(BUFFER_READER* reader, EXECUTE_RESULT* executeResult);
unsigned char bufferReaderReadUInt8(BUFFER_READER* reader, EXECUTE_RESULT* executeResult);
short bufferReaderReadInt16(BUFFER_READER* reader, EXECUTE_RESULT* executeResult);
unsigned short bufferReaderReadUInt16(BUFFER_READER* reader, EXECUTE_RESULT* executeResult);
int bufferReaderReadInt32(BUFFER_READER* reader, EXECUTE_RESULT* executeResult);
unsigned int bufferReaderReadUInt32(BUFFER_READER* reader, EXECUTE_RESULT* executeResult);
long bufferReaderReadInt64(BUFFER_READER* reader, EXECUTE_RESULT* executeResult);
unsigned long bufferReaderReadUInt64(BUFFER_READER* reader, EXECUTE_RESULT* executeResult);

#endif /* buffer_reader_interface_h */
