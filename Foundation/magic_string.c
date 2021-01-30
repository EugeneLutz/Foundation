//
//  magic_string.c
//  Foundation
//
//  Created by Евгений Лютц on 28.02.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

/*
 https://codereview.stackexchange.com/questions/197548/convert-utf8-string-to-utf32-string-in-c
 
 uint32_t* utf8_to_utf32(uint8_t* text) {
	 size_t num_chars = utf8_strlen(text);
	 uint32_t* c = malloc(sizeof(uint32_t) * num_chars);
	 size_t i = 0;

	 for (size_t n = 0; n < num_chars; n++) {
		 if ((text[i] & 0b10000000) == 0) {
			 // 1 byte code point, ASCII
			 c[n] = (text[i] & 0b01111111);
			 i += 1;
		 }
		 else if ((text[i] & 0b11100000) == 0b11000000) {
			 // 2 byte code point
			 c[n] = (text[i] & 0b00011111) << 6 | (text[i + 1] & 0b00111111);
			 i += 2;
		 }
		 else if ((text[i] & 0b11110000) == 0b11100000) {
			 // 3 byte code point
			 c[n] = (text[i] & 0b00001111) << 12 | (text[i + 1] & 0b00111111) << 6 | (text[i + 2] & 0b00111111);
			 i += 3;
		 }
		 else {
			 // 4 byte code point
			 c[n] = (text[i] & 0b00000111) << 18 | (text[i + 1] & 0b00111111) << 12 | (text[i + 2] & 0b00111111) << 6 | (text[i + 3] & 0b00111111);
			 i += 4;
		 }
	 }

	 return c;
 }
 */

// MARK: - Private interface

static unsigned int utf8_strlen(const char* text, size_t length)
{
	if (length == 0) {
		return 0;
	}
	
	size_t i = 0;
	size_t numChars = 0;

	while (i < length && text[i] != 0)
	{
		numChars++;
		
		// 1 byte code point, ASCII
		if ((text[i] & 0b10000000) == 0) {
			i += 1;
		}
		// 2 byte code point
		else if ((text[i] & 0b11100000) == 0b11000000) {
			i += 2;
		}
		// 3 byte code point
		else if ((text[i] & 0b11110000) == 0b11100000) {
			i += 3;
		}
		// 4 byte code point
		else {
			i += 4;
		}
	}

	return (unsigned int)numChars;
}

/*static unsigned int utf8_unsafe_strlen(const char* text)
{
	if (text == NULL) {
		return 0;
	}
	
	unsigned int i = 0;
	unsigned int numChars = 0;

	do
	{
		numChars++;
		
		// 1 byte code point, ASCII
		if ((text[i] & 0b10000000) == 0) {
			i += 1;
		}
		// 2 byte code point
		else if ((text[i] & 0b11100000) == 0b11000000) {
			i += 2;
		}
		// 3 byte code point
		else if ((text[i] & 0b11110000) == 0b11100000) {
			i += 3;
		}
		// 4 byte code point
		else {
			i += 4;
		}
		
		//assert(i <= length);
	} while (text[i] != 0);

	return numChars;
}*/


// MARK: - Public interface

STRING* stringCreateWithData(const char* data)
{
	unsigned int length = 0;
	if (data)
	{
		// TODO: replace to utf8_strlen
		// TODO: or not?
		length = (unsigned int)strlen(data);
	}
	return stringCreateWithDataAndLength(data, length);
}

STRING* stringCreateWithDataAndLength(const char* data, unsigned long length)
{
	STRING* string = malloc(sizeof(STRING));
	string->dataLength = length + 1;
	string->length = length;
	string->numCharacters = utf8_strlen(data, length);
	string->data = malloc(sizeof(char) * string->dataLength);
	
	if (data == NULL || length == 0)
	{
		string->data[0] = 0;
	}
	else
	{
		strncpy(string->data, data, length);
	}
	string->data[length] = 0;
	
	return string;
}

STRING* stringCreateCopy(STRING* string)
{
	assert(string);
	return stringCreateWithDataAndLength(string->data, string->length);
}

void stringRelease(STRING* string)
{
	assert(string);
	free(string->data);
	free(string);
}


void stringInitializeWithUTF8String(STRING* string, const char* utf8String)
{
	assert(string);
	
	unsigned int length = 0;
	if (utf8String)
	{
		length = (unsigned int)strlen(utf8String);
	}
	
	string->dataLength = length + 1;
	string->length = length;
	string->numCharacters = utf8_strlen(utf8String, string->length);
	string->data = malloc(string->dataLength);
	
	if (utf8String)
	{
		memcpy(string->data, utf8String, string->dataLength);
	}
	string->data[string->length] = 0;
}

void stringInitializeWithCopy(STRING* string, const STRING* copy)
{
	assert(string);
	assert(copy);
	
	string->dataLength = copy->dataLength;
	string->length = copy->length;
	string->numCharacters = copy->numCharacters;
	string->data = malloc(copy->dataLength);
	memcpy(string->data, copy->data, copy->dataLength);
}

void stringDeinitialize(STRING* string)
{
	assert(string);
	
	free(string->data);
#if DEBUG
	string->dataLength = 0;
	string->length = 0;
	string->numCharacters = 0;
	string->data = NULL;
#endif
}


unsigned int stringGetDataLength(STRING* string)
{
	assert(string);
	return (unsigned int)string->length;
}

const char* stringGetData(STRING* string)
{
	assert(string);
	return string->data;
}

unsigned int stringGetLength(STRING* string)
{
	assert(string);
	return (unsigned int)string->numCharacters;
}

unsigned int stringGetUTF32Character(STRING* string, unsigned long characterIndex)
{
	assert(string);
	assert(characterIndex < string->numCharacters);
	
	unsigned long currentCharacterIndex = 0;
	unsigned long i = 0;
	unsigned int value = 0;

	while (currentCharacterIndex != characterIndex)
	{
		// 1 byte code point, ASCII
		if ((string->data[i] & 0b10000000) == 0) {
			i += 1;
		}
		// 2 byte code point
		else if ((string->data[i] & 0b11100000) == 0b11000000) {
			i += 2;
		}
		// 3 byte code point
		else if ((string->data[i] & 0b11110000) == 0b11100000) {
			i += 3;
		}
		// 4 byte code point
		else {
			i += 4;
		}
		
		assert(i <= string->length);
		currentCharacterIndex++;
	}
	
	// 1 byte code point, ASCII
	if ((string->data[i] & 0b10000000) == 0)
	{
		value = (string->data[i] & 0b01111111);
	}
	// 2 byte code point
	else if ((string->data[i] & 0b11100000) == 0b11000000)
	{
		value = (string->data[i] & 0b00011111) << 6 | (string->data[i + 1] & 0b00111111);
	}
	// 3 byte code point
	else if ((string->data[i] & 0b11110000) == 0b11100000)
	{
		value = (string->data[i] & 0b00001111) << 12 | (string->data[i + 1] & 0b00111111) << 6 | (string->data[i + 2] & 0b00111111);
	}
	// 4 byte code point
	else
	{
		value = (string->data[i] & 0b00000111) << 18 | (string->data[i + 1] & 0b00111111) << 12 | (string->data[i + 2] & 0b00111111) << 6 | (string->data[i + 3] & 0b00111111);
	}
	
	return value;
}


void stringSet(STRING* string, STRING* source)
{
	assert(string);
	assert(source);
	
	string->dataLength = source->dataLength;
	string->length = source->length;
	string->numCharacters = source->numCharacters;
	
	free(string->data);
	string->data = malloc(string->dataLength);
	
	assert(string->data);
	memcpy(string->data, source->data, string->dataLength);
}

void stringSetData(STRING* string, const char* data)
{
	assert(string);
	
	if (data)
	{
		unsigned long length = (unsigned int)strlen(data);
		stringSetDataWithSubstring(string, data, 0, length);
		return;
	}
	
	stringSetDataWithSubstring(string, NULL, 0, 0);
}

// FIXME: count utf8 data
void stringSetDataWithLength(STRING* string, const char* data, unsigned long length)
{
	assert(string);
	stringSetDataWithSubstring(string, data, 0, length);
	/*if (data == NULL || length == 0) {
		string->length = 0;
		string->data[0] = 0;
		return;
	}
	
	if (length >= string->dataLength) {
		unsigned int newDataLength = length + 1;
		char* newData = realloc(string->data, newDataLength);
		assert(newData);
		string->dataLength = newDataLength;
		string->length = length;
		string->data = newData;
	}
	
	strncpy(string->data, data, length);
	string->data[length] = 0;*/
}

// FIXME: count utf8 data
void stringSetDataWithSubstring(STRING* string, const char* data, unsigned long start, unsigned long length)
{
	assert(string);
	
	if (data == NULL || length == 0)
	{
		string->length = 0;
		string->data[0] = 0;
		return;
	}
	
	if (string)
	{
		const char* truncatedData = &(data[start]);
		
		free(string->data);
		string->dataLength = length + 1;
		string->length = length;
		string->numCharacters = utf8_strlen(truncatedData, length);
		string->data = malloc(string->dataLength);
		memcpy(string->data, truncatedData, length);
		string->data[length] = 0;
		
		return;
	}
	
	if (length >= string->dataLength)
	{
		unsigned long newDataLength = length + 1;
		char* newData = realloc(string->data, newDataLength);
		assert(newData);
		string->dataLength = newDataLength;
		string->length = length;
		string->data = newData;
	}
	
	strncpy(string->data, data + sizeof(char) * start, length);
	string->data[length] = 0;
}

void stringCopy(STRING* destination, const STRING* source)
{
	assert(destination);
	assert(source);
	
	stringSetDataWithLength(destination, source->data, source->length);
}


void stringAppedData(STRING* string, const char* data)
{
	assert(string);
	
	if (data == NULL) {
		return;
	}
	
	size_t length = strlen(data);
	if (length == 0) {
		return;
	}
	
	size_t dataLength = string->length + length + 1;
	if (dataLength > string->dataLength)
	{
		char* data = realloc(string->data, dataLength);
		assert(data);
		string->data = data;
		string->dataLength = dataLength;
	}
	
	memcpy(&(string->data[string->length]), data, length);
	string->numCharacters += utf8_strlen(data, length);
	string->length += length;
}

static void _string_shiftData(STRING* string, unsigned long startIndex, long shiftValue)
{
	if (shiftValue == 0) {
		return;
	}
	
	size_t dataLength = string->length + shiftValue + 1;
	if (dataLength > string->dataLength)
	{
		char* data = realloc(string->data, dataLength);
		assert(data);
		string->data = data;
		string->dataLength = dataLength;
	}
	
	string->length = dataLength - 1;
	if (shiftValue > 0)
	{
		long endIndex = startIndex - shiftValue;
		for (long i = string->length; i >= endIndex; i--)
		{
			string->data[i + shiftValue] = string->data[i];
		}
	}
	else
	{
		for (long i = startIndex; i <= string->length; i++)
		{
			string->data[i] = string->data[i - shiftValue];
		}
	}
}

static int _string_checkCodePoint(char character, unsigned long* counter)
{
	if ((character & 0b10000000) == 0)
	{
		return 1;
	}
	else if ((character & 0b11100000) == 0b11000000)
	{
		(*counter) += 1;
	}
	else if ((character & 0b11110000) == 0b11100000)
	{
		(*counter) += 2;
	}
	else
	{
		(*counter) += 3;
	}
	
	return 0;
}

void stringReplaceData(STRING* string, const char* search, const char* replace)
{
	stringReplaceSubstrings(string, &search, &replace, 1);
}

void stringReplaceSubstrings(STRING* string, const char** search, const char** replace, unsigned long numElements)
{
	assert(string);
	assert(search);
	assert(replace);
	
	if (numElements == 0) {
		return;
	}
	
	typedef struct length_info {
		size_t slen;
		size_t rlen;
		long shiftValue;
	} length_info;
	
	length_info* lengths = malloc(sizeof(length_info) * numElements);
	for (int i = 0; i < numElements; i++)
	{
		length_info* info = &(lengths[i]);
		info->slen = strlen(search[i]);
		info->rlen = strlen(replace[i]);
		info->shiftValue = (long)info->rlen - (long)info->slen;
	}
	
	int modified = 0;
	
	for (unsigned long i = 0; i < string->length; i++)
	{
		char character = string->data[i];
		if (!_string_checkCodePoint(character, &i))
		{
			continue;
		}
		
		for (unsigned long k = 0; k < numElements; k++)
		{
			length_info* info = &(lengths[k]);
			size_t slen = info->slen;
			size_t rlen = info->rlen;
			long shiftValue = info->shiftValue;
			
			if (i + slen - 1 == string->length)
			{
				continue;
			}
			
			int equals = 1;
			for (long j = 0; j < slen; j++)
			{
				if (string->data[i + j] != search[k][j])
				{
					equals = 0;
					break;
				}
			}
			
			if (equals)
			{
				_string_shiftData(string, i + rlen, shiftValue);
				
				if (rlen)
				{
					memcpy(&(string->data[i]), replace[k], rlen);
				}
				
				modified = 1;
				
				i += rlen;
				break;
			}
		}
	}
	
	if (modified) {
		string->numCharacters = utf8_strlen(string->data, string->length);
	}
	
	free(lengths);
}


int stringCompareToData(STRING* string, const char* data)
{
	assert(string);
	
	//return strncmp(string->data, data, string->length);
	return strcmp(string->data, data);
}

int stringCompareToString(STRING* string, STRING* source)
{
	assert(string);
	assert(source);
	
	//return strncmp(string->data, source->data, string->length);
	return strcmp(string->data, source->data);
}
