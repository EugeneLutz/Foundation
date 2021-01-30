//
//  file_reader_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 25.12.2019.
//  Copyright © 2019 Eugene Lutz. All rights reserved.
//

#ifndef file_reader_interface_h
#define file_reader_interface_h

#include "foundation.h"

FILE_READER* systemOpenFileReader(SYSTEM* system, const char* filePath, FILE_MODE mode, EXECUTE_RESULT* executeResult);
void fileReaderClose(FILE_READER* reader, EXECUTE_RESULT* executeResult);

unsigned long fileReaderGetFileSize(FILE_READER* reader);

void fileReaderSetPosition(FILE_READER* reader, unsigned long position, EXECUTE_RESULT* executeResult);
void fileReaderReadToBuffer(FILE_READER* reader, BUFFER* buffer, unsigned long size, EXECUTE_RESULT* executeResult);

void fileReaderSkipLine(FILE_READER* reader, EXECUTE_RESULT* executeResult);
void fileReaderReadString(STRING* string, FILE_READER* reader, EXECUTE_RESULT* executeResult);
void fileReaderReadAllContentsToString(STRING* outString, FILE_READER* reader, EXECUTE_RESULT* executeResult);

double fileReaderReadStringAsDouble(FILE_READER* reader, EXECUTE_RESULT* executeResult);
float fileReaderReadStringAsFloat(FILE_READER* reader, EXECUTE_RESULT* executeResult);

unsigned int fileReaderReadStringAsUInt(FILE_READER* reader, EXECUTE_RESULT* executeResult);

int fileReaderReadStringAsInt(FILE_READER* reader, EXECUTE_RESULT* executeResult);

#endif /* file_reader_interface_h */
