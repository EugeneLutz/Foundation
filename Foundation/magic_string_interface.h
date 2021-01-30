//
//  magic_string_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 28.02.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef magic_string_interface_h
#define magic_string_interface_h

#include "foundation.h"

STRING* stringCreateWithData(const char* data);
STRING* stringCreateWithDataAndLength(const char* data, unsigned long length);
STRING* stringCreateCopy(STRING* string);
void stringRelease(STRING* string);

void stringInitializeWithUTF8String(STRING* string, const char* utf8String);
void stringInitializeWithCopy(STRING* string, const STRING* copy);
void stringDeinitialize(STRING* string);

unsigned int stringGetDataLength(STRING* string);
const char* stringGetData(STRING* string);
unsigned int stringGetLength(STRING* string);
unsigned int stringGetUTF32Character(STRING* string, unsigned long characterIndex);

void stringSet(STRING* string, STRING* source);
void stringSetData(STRING* string, const char* data);
void stringSetDataWithLength(STRING* string, const char* data, unsigned long length);
void stringSetDataWithSubstring(STRING* string, const char* data, unsigned long start, unsigned long length);
void stringCopy(STRING* destination, const STRING* source);

void stringAppedData(STRING* string, const char* data);
void stringReplaceData(STRING* string, const char* search, const char* replace);
void stringReplaceSubstrings(STRING* string, const char** search, const char** replace, unsigned long numElements);

int stringCompareToData(STRING* string, const char* data);
int stringCompareToString(STRING* string, STRING* source);

#endif /* magic_string_interface_h */
