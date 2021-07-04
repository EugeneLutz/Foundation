//
//  magic_dictionary.c
//  Foundation
//
//  Created by Евгений Лютц on 09.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

void magicDictionaryInitializeWithContentsOfJsonFileInMainBundle(MAGIC_DICTIONARY* dictionary, SYSTEM* system, const char* name, const char* extension, EXECUTE_RESULT* executeResult)
{
	STRING* filePath = stringCreateWithData(NULL);
	systemGetPathForResourceWithName(system, filePath, name, extension, executeResult);
	assert(executeResultIsSucceeded(executeResult));
	
	FILE_READER* reader = systemOpenFileReader(system, filePath->data, FILE_MODE_TEXT, executeResult);
	assert(executeResultIsSucceeded(executeResult));
	stringRelease(filePath);
	
	STRING* bufferData = stringCreateWithData(NULL);
	fileReaderReadAllContentsToString(bufferData, reader, executeResult);
	assert(executeResultIsSucceeded(executeResult));
	fileReaderClose(reader, executeResult);
	assert(executeResultIsSucceeded(executeResult));
	
	magicDictionaryInitialize(dictionary);
	magicDictionaryReadJsonUTF8Data(dictionary, bufferData->data, u8"root", 0, executeResult);
	assert(executeResultIsSucceeded(executeResult));
	stringRelease(bufferData);
}

void magicDictionaryInitialize(MAGIC_DICTIONARY* dictionary)
{
	assert(dictionary);
	
	magicArrayInitialize(&dictionary->elements, sizeof(MAGIC_DICTIONARY_KEY_VALUE_PAIR), 4);
	magicArrayInitialize(&dictionary->stringValues, sizeof(STRING), 4);
	magicArrayInitialize(&dictionary->arrayValues, sizeof(MAGIC_ARRAY), 4);
	magicArrayInitialize(&dictionary->dictionaryValues, sizeof(MAGIC_DICTIONARY), 4);
}

void magicDictionaryDeinitialize(MAGIC_DICTIONARY* dictionary)
{
	assert(dictionary);
	
	for (unsigned long i = 0; i < dictionary->dictionaryValues.length; i++)
	{
		MAGIC_DICTIONARY* magicDictionary = magicArrayGetItem(&dictionary->dictionaryValues, i);
		magicDictionaryDeinitialize(magicDictionary);
	}
	magicArrayDeinitialize(&dictionary->dictionaryValues);
	
	for (unsigned long i = 0; i < dictionary->arrayValues.length; i++)
	{
		MAGIC_ARRAY* array = magicArrayGetItem(&dictionary->arrayValues, i);
		magicArrayDeinitialize(array);
	}
	magicArrayDeinitialize(&dictionary->arrayValues);
	
	for (unsigned long i = 0; i < dictionary->stringValues.length; i++)
	{
		STRING* string = magicArrayGetItem(&dictionary->stringValues, i);
		stringDeinitialize(string);
	}
	magicArrayDeinitialize(&dictionary->stringValues);
	
	for (unsigned long i = 0; i < dictionary->elements.length; i++)
	{
		MAGIC_DICTIONARY_KEY_VALUE_PAIR* pair = magicArrayGetItem(&dictionary->elements, i);
		stringDeinitialize(&pair->key);
	}
	magicArrayDeinitialize(&dictionary->elements);
}


MAGIC_DICTIONARY_ELEMENT* magicDictionaryGetItemWithKey(MAGIC_DICTIONARY* dictionary, const char* keyData)
{
	assert(dictionary);
	assert(keyData);
	
	for (unsigned long i = 0; i < dictionary->elements.length; i++)
	{
		MAGIC_DICTIONARY_KEY_VALUE_PAIR* pair = magicArrayGetItem(&dictionary->elements, i);
		if (stringCompareToData(&pair->key, keyData) == 0)
		{
			return &pair->value;
		}
	}
	
	return NULL;
}


MAGIC_DICTIONARY_ELEMENT_TYPE magicDictionaryElementGetType(MAGIC_DICTIONARY_ELEMENT* element)
{
	assert(element);
	return element->type;
}

MAGIC_ARRAY* magicDictionaryElementGetArrayValue(MAGIC_DICTIONARY_ELEMENT* element)
{
	assert(element);
	assert(element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_ARRAY);
	return element->arrayValue;
}

MAGIC_DICTIONARY* magicDictionaryElementGetDictionaryValue(MAGIC_DICTIONARY_ELEMENT* element)
{
	assert(element);
	assert(element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_DICTIONARY);
	return element->dictionaryValue;
}


int magicDictionaryGetBoolean(MAGIC_DICTIONARY* dictionary, const char* key, EXECUTE_RESULT* executeResult)
{
	assert(dictionary);
	assert(key);
	
	MAGIC_DICTIONARY_ELEMENT* element = magicDictionaryGetItemWithKey(dictionary, key);
	if (element == NULL) {
		executeResultSetFailed(executeResult, "Key-value pair with given key is not found.");
		return 0;
	}
	
	if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_LONG) {
		return (int)element->longValue;
	}
	
	executeResultSetFailed(executeResult, "Cannot convert a value at given key to boolean type.");
	return 0;
}

long magicDictionaryGetLong(MAGIC_DICTIONARY* dictionary, const char* key, EXECUTE_RESULT* executeResult)
{
	assert(dictionary);
	assert(key);
	
	MAGIC_DICTIONARY_ELEMENT* element = magicDictionaryGetItemWithKey(dictionary, key);
	if (element == NULL) {
		executeResultSetFailed(executeResult, "Key-value pair with given key is not found.");
		return 0;
	}
	
	if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_FLOAT) {
		return (long)element->floatValue;
	}
	else if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_DOUBLE) {
		return (long)element->doubleValue;
	}
	else if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_LONG) {
		return element->longValue;
	}
	
	executeResultSetFailed(executeResult, "Cannot convert a value at given key to long type.");
	return 0;
}

float magicDictionaryGetFloat(MAGIC_DICTIONARY* dictionary, const char* key, EXECUTE_RESULT* executeResult)
{
	assert(dictionary);
	assert(key);
	
	MAGIC_DICTIONARY_ELEMENT* element = magicDictionaryGetItemWithKey(dictionary, key);
	if (element == NULL) {
		executeResultSetFailed(executeResult, "Key-value pair with given key is not found.");
		return 0.0f;
	}
	
	if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_FLOAT) {
		return element->floatValue;
	}
	else if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_DOUBLE) {
		return (float)element->doubleValue;
	}
	else if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_LONG) {
		return (float)element->longValue;
	}
	
	executeResultSetFailed(executeResult, "Cannot convert a value at given key to float type.");
	return 0.0f;
}

STRING* magicDictionaryGetString(MAGIC_DICTIONARY* dictionary, const char* key, EXECUTE_RESULT* executeResult)
{
	assert(dictionary);
	assert(key);
	
	MAGIC_DICTIONARY_ELEMENT* element = magicDictionaryGetItemWithKey(dictionary, key);
	if (element == NULL) {
		executeResultSetFailed(executeResult, "Key-value pair with given key is not found.");
		return NULL;
	}
	
	if (element->type != MAGIC_DICTIONARY_ELEMENT_TYPE_STRING) {
		executeResultSetFailed(executeResult, "Value at given key is not of string type.");
		return NULL;
	}
	
	return element->stringValue;
}

MAGIC_ARRAY* magicDictionaryGetArray(MAGIC_DICTIONARY* dictionary, const char* key, EXECUTE_RESULT* executeResult)
{
	assert(dictionary);
	assert(key);
	
	MAGIC_DICTIONARY_ELEMENT* element = magicDictionaryGetItemWithKey(dictionary, key);
	if (element == NULL) {
		executeResultSetFailed(executeResult, "Key-value pair with given key is not found.");
		return NULL;
	}
	
	if (element->type != MAGIC_DICTIONARY_ELEMENT_TYPE_ARRAY) {
		executeResultSetFailed(executeResult, "Value at given key is not of magic array type.");
		return NULL;
	}
	
	return element->arrayValue;
}

MAGIC_DICTIONARY* magicDictionaryGetDictionary(MAGIC_DICTIONARY* dictionary, const char* key, EXECUTE_RESULT* executeResult)
{
	MAGIC_DICTIONARY_ELEMENT* element = magicDictionaryGetItemWithKey(dictionary, key);
	if (element == NULL) {
		executeResultSetFailed(executeResult, "Key-value pair with given key is not found.");
		return NULL;
	}
	
	if (element->type != MAGIC_DICTIONARY_ELEMENT_TYPE_DICTIONARY) {
		executeResultSetFailed(executeResult, "Value at given key is not of dictionary type.");
		return NULL;
	}
	
	return element->dictionaryValue;
}

vector2f magicDictionaryGetVector2f(MAGIC_DICTIONARY* dictionary, const char* xKey, const char* yKey, EXECUTE_RESULT* executeResult)
{
	assert(dictionary);
	assert(xKey);
	assert(yKey);
	
	float xValue = 0.0f;
	float yValue = 0.0f;
	
	MAGIC_DICTIONARY_ELEMENT* element = magicDictionaryGetItemWithKey(dictionary, xKey);
	if (element == NULL) {
		executeResultSetFailed(executeResult, "Key-value pair with given key is not found.");
		return vector2fNull();
	}
	
	if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_FLOAT) {
		xValue = element->floatValue;
	}
	else if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_DOUBLE) {
		xValue = (float)element->doubleValue;
	}
	else if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_LONG) {
		xValue = (float)element->longValue;
	}
	else {
		executeResultSetFailed(executeResult, "Value at given key is not of string type.");
		return vector2fNull();
	}
	
	
	element = magicDictionaryGetItemWithKey(dictionary, yKey);
	if (element == NULL) {
		executeResultSetFailed(executeResult, "Key-value pair with given key is not found.");
		return vector2fNull();
	}
	
	if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_FLOAT) {
		yValue = element->floatValue;
	}
	else if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_DOUBLE) {
		yValue = (float)element->doubleValue;
	}
	else if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_LONG) {
		yValue = (float)element->longValue;
	}
	else {
		executeResultSetFailed(executeResult, "Value at given key is not of string type.");
		return vector2fNull();
	}
	
	return vector2fCreate(xValue, yValue);
}


MAGIC_DICTIONARY_ELEMENT* magicDictionaryArrayGetItem(MAGIC_ARRAY* array, unsigned long index)
{
	return magicArrayGetItem(array, index);
}


MAGIC_DICTIONARY* magicDictionaryArrayGetDictionary(MAGIC_ARRAY* array, unsigned long index, EXECUTE_RESULT* executeResult)
{
	MAGIC_DICTIONARY_ELEMENT* element = magicDictionaryArrayGetItem(array, index);
	if (element == NULL) {
		executeResultSetFailed(executeResult, "Cannot find dictionary value at given index.");
		return NULL;
	}
	
	if (element->type != MAGIC_DICTIONARY_ELEMENT_TYPE_DICTIONARY) {
		executeResultSetFailed(executeResult, "Value at given index is not of dictionary type.");
		return NULL;
	}
	
	return element->dictionaryValue;
}

STRING* magicDictionaryArrayGetString(MAGIC_ARRAY* array, unsigned long index, EXECUTE_RESULT* executeResult)
{
	MAGIC_DICTIONARY_ELEMENT* element = magicDictionaryArrayGetItem(array, index);
	if (element == NULL) {
		executeResultSetFailed(executeResult, "Cannot find string value at given index.");
		return NULL;
	}
	
	if (element->type != MAGIC_DICTIONARY_ELEMENT_TYPE_STRING) {
		executeResultSetFailed(executeResult, "Value at given index is not of string type.");
		return NULL;
	}
	
	return element->stringValue;
}
