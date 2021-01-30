//
//  magic_dictionary_export_to_json_string.c
//  Foundation
//
//  Created by Евгений Лютц on 13.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

extern const char* _magicDictionary_escapedJsonSymbols[];
extern const char* _magicDictionary_jsonSymbolsToEscape[];
extern const size_t _magicDictionary_numJsonEscapeSymbols;

static void _magicDictionaryArray_appedJSONString(MAGIC_ARRAY* array, STRING* outJsonString, EXECUTE_RESULT* executeResult, int hierarchyLevel, unsigned int printLeadingOffset, STRING* temporaryString);
static void _magicDictionary_appedJSONString(MAGIC_DICTIONARY* dictionary, STRING* outJsonString, EXECUTE_RESULT* executeResult, int hierarchyLevel, unsigned int printLeadingOffset, STRING* temporaryString);

static void _jsonString_printHierarchyOffset(STRING* outJsonString, int hierarchyLevel)
{
	for (unsigned int j = 0; j < hierarchyLevel; j++) {
		stringAppedData(outJsonString, "\t");
	}
}

static void _jsonString_printElement(STRING* outJsonString, MAGIC_DICTIONARY_ELEMENT* element, EXECUTE_RESULT* executeResult, int hierarchyLevel, int isDictionaryValue, STRING* temporaryString)
{
	if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_LONG)
	{
		if (isDictionaryValue) {
			stringAppedData(outJsonString, " ");
		}
		
		char numberData[64];
		sprintf(numberData, "%ld", element->longValue);
		stringAppedData(outJsonString, numberData);
	}
	else if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_DOUBLE)
	{
		if (isDictionaryValue) {
			stringAppedData(outJsonString, " ");
		}
		
		char numberData[64];
		sprintf(numberData, "%f", element->doubleValue);
		stringAppedData(outJsonString, numberData);
	}
	else if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_STRING)
	{
		if (isDictionaryValue) {
			stringAppedData(outJsonString, " ");
		}
		
		stringCopy(temporaryString, element->stringValue);
		stringReplaceSubstrings(temporaryString, _magicDictionary_jsonSymbolsToEscape, _magicDictionary_escapedJsonSymbols, _magicDictionary_numJsonEscapeSymbols);
		
		stringAppedData(outJsonString, "\"");
		stringAppedData(outJsonString, temporaryString->data);
		stringAppedData(outJsonString, "\"");
	}
	else if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_ARRAY)
	{
		if (isDictionaryValue) {
			stringAppedData(outJsonString, "\n");
			_magicDictionaryArray_appedJSONString(element->arrayValue, outJsonString, executeResult, hierarchyLevel, 1, temporaryString);
		}
		else {
			_magicDictionaryArray_appedJSONString(element->arrayValue, outJsonString, executeResult, hierarchyLevel, 0, temporaryString);
		}
	}
	else if (element->type == MAGIC_DICTIONARY_ELEMENT_TYPE_DICTIONARY)
	{
		if (isDictionaryValue) {
			stringAppedData(outJsonString, "\n");
			_magicDictionary_appedJSONString(element->dictionaryValue, outJsonString, executeResult, hierarchyLevel, 1, temporaryString);
		}
		else {
			_magicDictionary_appedJSONString(element->dictionaryValue, outJsonString, executeResult, hierarchyLevel, 0, temporaryString);
		}
	}
	else
	{
		if (isDictionaryValue) {
			stringAppedData(outJsonString, " ");
		}
		stringAppedData(outJsonString, "\"<unknown value type>\"");
	}
}

static void _magicDictionaryArray_appedJSONString(MAGIC_ARRAY* array, STRING* outJsonString, EXECUTE_RESULT* executeResult, int hierarchyLevel, unsigned int printLeadingOffset, STRING* temporaryString)
{
	if (printLeadingOffset) {
		_jsonString_printHierarchyOffset(outJsonString, hierarchyLevel);
	}
	stringAppedData(outJsonString, "[\n");
	hierarchyLevel++;
	
	for (unsigned int i = 0; i < array->length; i++)
	{
		_jsonString_printHierarchyOffset(outJsonString, hierarchyLevel);
		
		MAGIC_DICTIONARY_ELEMENT* element = magicArrayGetItem(array, i);
		_jsonString_printElement(outJsonString, element, executeResult, hierarchyLevel, 0, temporaryString);
		
		if (i + 1 < array->length) {
			stringAppedData(outJsonString, ",\n");
		}
		else {
			stringAppedData(outJsonString, "\n");
		}
	}
	
	hierarchyLevel--;
	_jsonString_printHierarchyOffset(outJsonString, hierarchyLevel);
	stringAppedData(outJsonString, "]");
}

static void _magicDictionary_appedJSONString(MAGIC_DICTIONARY* dictionary, STRING* outJsonString, EXECUTE_RESULT* executeResult, int hierarchyLevel, unsigned int printLeadingOffset, STRING* temporaryString)
{
	if (printLeadingOffset) {
		_jsonString_printHierarchyOffset(outJsonString, hierarchyLevel);
	}
	stringAppedData(outJsonString, "{\n");
	hierarchyLevel++;
	
	for (unsigned int i = 0; i < dictionary->elements.length; i++)
	{
		MAGIC_DICTIONARY_KEY_VALUE_PAIR* pair = magicArrayGetItem(&dictionary->elements, i);
		
		stringCopy(temporaryString, &pair->key);
		stringReplaceSubstrings(temporaryString, _magicDictionary_jsonSymbolsToEscape, _magicDictionary_escapedJsonSymbols, _magicDictionary_numJsonEscapeSymbols);
		
		_jsonString_printHierarchyOffset(outJsonString, hierarchyLevel);
		stringAppedData(outJsonString, "\"");
		stringAppedData(outJsonString, temporaryString->data);
		stringAppedData(outJsonString, "\":");
		
		_jsonString_printElement(outJsonString, &pair->value, executeResult, hierarchyLevel, 1, temporaryString);
		
		if (i + 1 < dictionary->elements.length) {
			stringAppedData(outJsonString, ",\n");
		}
		else {
			stringAppedData(outJsonString, "\n");
		}
	}
	
	hierarchyLevel--;
	_jsonString_printHierarchyOffset(outJsonString, hierarchyLevel);
	stringAppedData(outJsonString, "}");
}

void magicDictionaryExportToJsonString(MAGIC_DICTIONARY* dictionary, STRING* outJsonString, EXECUTE_RESULT* executeResult)
{
	assert(dictionary);
	assert(outJsonString);
	
	executeResultSetSucceeded(executeResult);
	
	STRING resultString;
	stringInitializeWithUTF8String(&resultString, "\n\n");
	
	STRING temporaryString;
	stringInitializeWithUTF8String(&temporaryString, "");
	
	_magicDictionary_appedJSONString(dictionary, &resultString, executeResult, 0, 1, &temporaryString);
	if (executeResultIsFailed(executeResult)) {
		stringDeinitialize(&resultString);
		return;
	}
	
	stringDeinitialize(&temporaryString);
	
	stringCopy(outJsonString, &resultString);
	stringDeinitialize(&resultString);
	
	return;
}
