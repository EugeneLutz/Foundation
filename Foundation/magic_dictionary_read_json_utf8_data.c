//
//  magic_dictionary_read_json_utf8_data.c
//  Foundation
//
//  Created by Евгений Лютц on 13.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

#define is_cp1(value)	((value & 0b10000000) == 0b00000000)
#define is_cp2(value)	((value & 0b11100000) == 0b11000000)
#define is_cp3(value)	((value & 0b11110000) == 0b11100000)
#define is_cp4(value)	(!is_cp1(value) && !is_cp2(value) && !is_cp3(value))

// Checks for tab, space, new line
#define is_empty_character(character) (\
(character) == 0x09 ||	\
(character) == 0x20 ||	\
(character) == 0xA		\
)

// Checks for JSON escape character
/*
 Backspace to be replaced with \b
 Form feed to be replaced with \f
 Newline to be replaced with \n
 Carriage return to be replaced with \r
 Tab to be replaced with \t
 Double quote to be replaced with \"
 Backslash to be replaced with \\
 */
#define is_json_escape_character(character) (\
(character) == 'b' || \
(character) == 'f' || \
(character) == 'n' || \
(character) == 'r' || \
(character) == 't' || \
(character) == '"' || \
(character) == '\\' \
)

const char* _magicDictionary_escapedJsonSymbols[] = { "\\\\", "\\\"", "\\n", "\\r", "\\t", "\\b", "\\f" };
const char* _magicDictionary_jsonSymbolsToEscape[] = {  "\\",  "\"",   "\n",  "\r",  "\t",  "\b",  "\f" };
const size_t _magicDictionary_numJsonEscapeSymbols = sizeof(_magicDictionary_jsonSymbolsToEscape) / sizeof(char*);

static void _magicDictionary_unexpectedSymbol(EXECUTE_RESULT* executeResult, unsigned int currentCharacterNumber)
{
	char message[128];
	sprintf(message, "An unexpected symbol found while parsing JSON data at character %u.", currentCharacterNumber);
	executeResultSetFailed(executeResult, message);
}

static void _magicDictionary_readJsonString(const char* jsonUTF8Data, unsigned int dataLength, unsigned int* i, unsigned int* currentCharacterNumber, STRING* outString, EXECUTE_RESULT* executeResult)
{
	(*i)++;
	(*currentCharacterNumber)++;
		
	
	const unsigned int stringStartIndex = *i;
	
	for (; *i < dataLength; (*i)++, (*currentCharacterNumber)++)
	{
		const char character = jsonUTF8Data[*i];
		
		if (!is_cp1(character))
		{
			if (is_cp2(character)) {
				(*i) += 1;
			} else if (is_cp3(character)) {
				(*i) += 2;
			} else {
				(*i) += 3;
			}
		}
		else if (character == '"')
		{
			stringSetDataWithSubstring(outString, jsonUTF8Data, stringStartIndex, *i - stringStartIndex);
			
			stringReplaceSubstrings(outString, _magicDictionary_escapedJsonSymbols, _magicDictionary_jsonSymbolsToEscape, _magicDictionary_numJsonEscapeSymbols);
			
			return;
		}
		else if (character == '\\')
		{
			(*i) += 1;
			const char escapeSymbol = jsonUTF8Data[*i];
			if (!is_json_escape_character(escapeSymbol))
			{
				_magicDictionary_unexpectedSymbol(executeResult, *currentCharacterNumber);
				return;
			}
		}
	}
	
	executeResultSetFailed(executeResult, "Cannot find ending of string data");
}

typedef enum SF_JSON_NUMBER_TYPE
{
	SF_JSON_NUMBER_TYPE_UNKNOWN = 0,
	SF_JSON_NUMBER_TYPE_BOOLEAN,
	SF_JSON_NUMBER_TYPE_INTEGER,
	SF_JSON_NUMBER_TYPE_DOUBLE
}
SF_JSON_NUMBER_TYPE;

typedef struct SF_JSON_NUMBER
{
	STRING* temporaryData;
	
	SF_JSON_NUMBER_TYPE type;
	union
	{
		int booleanValue;	// true = 1; false = 0
		long integerValue;
		double doubleValue;
	};
}
SF_JSON_NUMBER;

static void _magicDictionary_readJsonNumber(const char* jsonUTF8Data, unsigned int dataLength, unsigned int* i, unsigned int* currentCharacterNumber, SF_JSON_NUMBER* outNumber, EXECUTE_RESULT* executeResult)
{
	const unsigned int numberStartIndex = *i;
	SF_JSON_NUMBER_TYPE type = SF_JSON_NUMBER_TYPE_UNKNOWN;

	for (; *i < dataLength; (*i)++, (*currentCharacterNumber)++)
	{
		const char character = jsonUTF8Data[*i];
		
		if ((character >= '0' && character <= '9') || (character == '.') || (character == '-'))
		{
			if (character == '.')
			{
				if (type == SF_JSON_NUMBER_TYPE_DOUBLE)
				{
					_magicDictionary_unexpectedSymbol(executeResult, *currentCharacterNumber);
					return;
				}
				
				type = SF_JSON_NUMBER_TYPE_DOUBLE;
			}
			else
			{
				if (character == '-' && numberStartIndex != (*i))
				{
					_magicDictionary_unexpectedSymbol(executeResult, *currentCharacterNumber);
					return;
				}
				
				if (type == SF_JSON_NUMBER_TYPE_UNKNOWN)
				{
					type = SF_JSON_NUMBER_TYPE_INTEGER;
				}
			}
		}
		else
		{
			outNumber->type = type;
			
			if (type == SF_JSON_NUMBER_TYPE_UNKNOWN)
			{
				char message[128];
				sprintf(message, "An unexpected symbol found while parsing JSON number at character %u. A number value is not found.", *currentCharacterNumber);
				executeResultSetFailed(executeResult, message);
				return;
			}
			
			const unsigned int numberStringLen = (*i) - numberStartIndex;
			stringSetDataWithSubstring(outNumber->temporaryData, jsonUTF8Data, numberStartIndex, numberStringLen);
			
			if (type == SF_JSON_NUMBER_TYPE_INTEGER)
			{
				outNumber->integerValue = atol(outNumber->temporaryData->data);
			}
			else if (type == SF_JSON_NUMBER_TYPE_DOUBLE)
			{
				outNumber->doubleValue = atof(outNumber->temporaryData->data);
			}
			
			(*i)--;
			(*currentCharacterNumber)--;
			
			return;
		}
	}
	
	executeResultSetFailed(executeResult, "Cannot find ending of string data");
}

void magicDictionaryReadJsonUTF8Data(MAGIC_DICTIONARY* dictionary, const char* jsonUTF8Data, const char* rootName, int dontUseRootObjectForDictionary, EXECUTE_RESULT* executeResult)
{
	assert(dictionary);
	assert(jsonUTF8Data);
	assert(rootName);
	
	typedef enum PARSER_STATE
	{
		PARSER_STATE_ROOT = 0,
		PARSER_STATE_DICTIONARY,
		PARSER_STATE_DICTIONARY_LOOKING_FOR_KEY_VALUE_SEPARATOR,
		PARSER_STATE_DICTIONARY_LOOKING_FOR_VALUE,
		PARSER_STATE_DICTIONARY_FOUND_VALUE,
		PARSER_STATE_DICTIONARY_FOUND_VALUE_SEPARATOR,
		PARSER_STATE_ARRAY,
		PARSER_STATE_ARRAY_FOUND_VALUE,
		PARSER_STATE_ARRAY_FOUND_VALUE_SEPARATOR
	}
	PARSER_STATE;
	
	typedef struct PARSER_DATA
	{
		PARSER_STATE state;
		
		union
		{
			struct {
				int foundElement;
				int foundOpeningCurlyBracket;
				int foundOpeningSquareBracket;
			} root;
			
			struct {
				MAGIC_DICTIONARY* dictionary;
			} dictionary;
			
			struct {
				MAGIC_ARRAY* array;
			} array;
		};
	}
	PARSER_DATA;
	
	executeResultSetSucceeded(executeResult);
	
	MAGIC_ARRAY parserStack;
	magicArrayInitialize(&parserStack, sizeof(PARSER_DATA), 4);
	PARSER_DATA* parseData = magicArrayAddItem(&parserStack);
	parseData->state = PARSER_STATE_ROOT;
	parseData->root.foundElement = 0;
	parseData->root.foundOpeningCurlyBracket = 0;
	parseData->root.foundOpeningSquareBracket = 0;
	
	STRING* keyString = stringCreateWithData(u8"");
	STRING* valueString = stringCreateWithData(u8"");
	SF_JSON_NUMBER valueNumber;
	valueNumber.temporaryData = stringCreateWithData(u8"");
	
	unsigned int currentCharacterNumber = 1;
	
	const unsigned int dataLength = (unsigned int)strlen(jsonUTF8Data);
	for (unsigned int i = 0; i < dataLength; i++, currentCharacterNumber++)
	{
		const char character = jsonUTF8Data[i];
		const unsigned int parseStackIndex = magicArrayGetLength(&parserStack) - 1;
		parseData = magicArrayGetItem(&parserStack, parseStackIndex);
		
		if (parseData->state == PARSER_STATE_ROOT)
		{
			if (is_empty_character(character))
			{
				continue;
			}
			else if (character == '{')
			{
				if (parseData->root.foundElement)
				{
					char message[256];
					sprintf(message, "An unexpected symbol found while parsing JSON data at character %u.", currentCharacterNumber);
					if (parseData->root.foundOpeningCurlyBracket) {
						sprintf(message, "%s Curly brackets were already opened and closed.", message);
					}
					else if (parseData->root.foundOpeningSquareBracket) {
						sprintf(message, "%s Square brackets were previously opened and closed.", message);
					}
					executeResultSetFailed(executeResult, message);
					break;
				}
				else
				{
					if (dontUseRootObjectForDictionary)
					{
						//
					}
					else
					{
						//
					}
					
					parseData->root.foundElement = 1;
					parseData->root.foundOpeningCurlyBracket = 1;
					
					parseData = magicArrayAddItem(&parserStack);
					parseData->state = PARSER_STATE_DICTIONARY;
					parseData->dictionary.dictionary = dictionary;
					continue;
				}
			}
			else if (character == '[')
			{
				if (parseData->root.foundElement)
				{
					char message[256];
					sprintf(message, "An unexpected symbol found while parsing JSON data at character %u", currentCharacterNumber);
					if (parseData->root.foundOpeningCurlyBracket) {
						sprintf(message, "%s Curly brackets were previously opened and closed.", message);
					}
					else if (parseData->root.foundOpeningSquareBracket) {
						sprintf(message, "%s Square brackets were already opened and closed.", message);
					}
					executeResultSetFailed(executeResult, message);
					break;
				}
				else
				{
					parseData->root.foundElement = 1;
					parseData->root.foundOpeningSquareBracket = 1;
					
					parseData->state = PARSER_STATE_DICTIONARY_FOUND_VALUE;
					
					MAGIC_DICTIONARY_KEY_VALUE_PAIR* pair = magicArrayAddItem(&dictionary->elements);
					stringInitializeWithUTF8String(&pair->key, rootName);
					
					// dictionary->dictionaryValue not parseData->dictionary.dictionary->arrayValues !!!
					MAGIC_ARRAY* value = magicArrayAddItem(&dictionary->arrayValues);
					magicArrayInitialize(value, sizeof(MAGIC_DICTIONARY_ELEMENT), 2);
					pair->value.type = MAGIC_DICTIONARY_ELEMENT_TYPE_ARRAY;
					pair->value.arrayValue = value;
					
					parseData = magicArrayAddItem(&parserStack);
					parseData->state = PARSER_STATE_ARRAY;
					parseData->array.array = value;
					
					continue;
				}
			}
			else if (character == '}')
			{
				char message[256];
				sprintf(message, "An unexpected symbol found while parsing JSON data at character %u.", currentCharacterNumber);
				if (parseData->root.foundOpeningCurlyBracket) {
					sprintf(message, "%s Curly brackets were already opened and closed.", message);
				}
				else if (parseData->root.foundOpeningSquareBracket) {
					sprintf(message, "%s Square brackets were previously opened and closed.", message);
				}
				executeResultSetFailed(executeResult, message);
				break;
			}
			else if (character == ']')
			{
				char message[256];
				sprintf(message, "An unexpected symbol found while parsing JSON data at character %u.", currentCharacterNumber);
				if (parseData->root.foundOpeningCurlyBracket) {
					sprintf(message, "%s Curly brackets were previously opened and closed.", message);
				}
				else if (parseData->root.foundOpeningSquareBracket) {
					sprintf(message, "%s Square brackets were already opened and closed.", message);
				}
				executeResultSetFailed(executeResult, message);
				break;
			}
			else
			{
				_magicDictionary_unexpectedSymbol(executeResult, currentCharacterNumber);
				break;
			}
		}
		else if (parseData->state == PARSER_STATE_DICTIONARY)
		{
			if (is_empty_character(character))
			{
				continue;
			}
			else if (character == '"')
			{
				_magicDictionary_readJsonString(jsonUTF8Data, dataLength, &i, &currentCharacterNumber, keyString, executeResult);
				if (executeResultIsFailed(executeResult)) {
					break;
				}
				
				parseData->state = PARSER_STATE_DICTIONARY_LOOKING_FOR_KEY_VALUE_SEPARATOR;
				continue;
			}
			else if (character == '}')
			{
				magicArrayRemoveItemByIndex(&parserStack, parseStackIndex);
				continue;
			}
			else
			{
				_magicDictionary_unexpectedSymbol(executeResult, currentCharacterNumber);
				break;
			}
		}
		else if (parseData->state == PARSER_STATE_DICTIONARY_LOOKING_FOR_KEY_VALUE_SEPARATOR)
		{
			if (is_empty_character(character))
			{
				continue;
			}
			else if (character == ':')
			{
				parseData->state = PARSER_STATE_DICTIONARY_LOOKING_FOR_VALUE;
			}
			else
			{
				_magicDictionary_unexpectedSymbol(executeResult, currentCharacterNumber);
				break;
			}
		}
		else if (parseData->state == PARSER_STATE_DICTIONARY_LOOKING_FOR_VALUE)
		{
			if (is_empty_character(character))
			{
				continue;
			}
			else if (character == '\"')
			{
				_magicDictionary_readJsonString(jsonUTF8Data, dataLength, &i, &currentCharacterNumber, valueString, executeResult);
				if (executeResultIsFailed(executeResult)) {
					break;
				}
				
				MAGIC_DICTIONARY_KEY_VALUE_PAIR* pair = magicArrayAddItem(&parseData->dictionary.dictionary->elements);
				stringInitializeWithCopy(&pair->key, keyString);
				
				// dictionary->stringValues not parseData->dictionary.dictionary->stringValues !!!
				STRING* value = magicArrayAddItem(&dictionary->stringValues);
				stringInitializeWithCopy(value, valueString);
				pair->value.type = MAGIC_DICTIONARY_ELEMENT_TYPE_STRING;
				pair->value.stringValue = value;
				
				
				parseData->state = PARSER_STATE_DICTIONARY_FOUND_VALUE;
				continue;
			}
			else if ((character >= '0' && character <= '9') || (character == '.') || (character == '-'))
			{
				_magicDictionary_readJsonNumber(jsonUTF8Data, dataLength, &i, &currentCharacterNumber, &valueNumber, executeResult);
				if (executeResultIsFailed(executeResult)) {
					break;
				}
				
				MAGIC_DICTIONARY_KEY_VALUE_PAIR* pair = magicArrayAddItem(&parseData->dictionary.dictionary->elements);
				stringInitializeWithCopy(&pair->key, keyString);
				switch (valueNumber.type)
				{
					case SF_JSON_NUMBER_TYPE_INTEGER:
						pair->value.type = MAGIC_DICTIONARY_ELEMENT_TYPE_LONG;
						pair->value.longValue = valueNumber.integerValue;
						break;
					
					case SF_JSON_NUMBER_TYPE_DOUBLE:
						pair->value.type = MAGIC_DICTIONARY_ELEMENT_TYPE_DOUBLE;
						pair->value.doubleValue = valueNumber.doubleValue;
						break;
						
					default:
						assert(0);
						break;
				}
				
				parseData->state = PARSER_STATE_DICTIONARY_FOUND_VALUE;
				continue;
			}
			else if (character == '{')
			{
				parseData->state = PARSER_STATE_DICTIONARY_FOUND_VALUE;
				
				MAGIC_DICTIONARY_KEY_VALUE_PAIR* pair = magicArrayAddItem(&parseData->dictionary.dictionary->elements);
				stringInitializeWithCopy(&pair->key, keyString);
				
				// dictionary->dictionaryValue not parseData->dictionary.dictionary->dictionaryValues !!!
				MAGIC_DICTIONARY* value = magicArrayAddItem(&dictionary->dictionaryValues);
				magicDictionaryInitialize(value);
				pair->value.type = MAGIC_DICTIONARY_ELEMENT_TYPE_DICTIONARY;
				pair->value.dictionaryValue = value;
				
				parseData = magicArrayAddItem(&parserStack);
				parseData->state = PARSER_STATE_DICTIONARY;
				parseData->dictionary.dictionary = value;
				
				continue;
			}
			else if (character == '[')
			{
				parseData->state = PARSER_STATE_DICTIONARY_FOUND_VALUE;
				
				MAGIC_DICTIONARY_KEY_VALUE_PAIR* pair = magicArrayAddItem(&parseData->dictionary.dictionary->elements);
				stringInitializeWithCopy(&pair->key, keyString);
				
				// dictionary->dictionaryValue not parseData->dictionary.dictionary->arrayValues !!!
				MAGIC_ARRAY* value = magicArrayAddItem(&dictionary->arrayValues);
				magicArrayInitialize(value, sizeof(MAGIC_DICTIONARY_ELEMENT), 2);
				pair->value.type = MAGIC_DICTIONARY_ELEMENT_TYPE_ARRAY;
				pair->value.arrayValue = value;
				
				parseData = magicArrayAddItem(&parserStack);
				parseData->state = PARSER_STATE_ARRAY;
				parseData->array.array = value;
				
				continue;
			}
			else
			{
				_magicDictionary_unexpectedSymbol(executeResult, currentCharacterNumber);
				break;
			}
		}
		else if (parseData->state == PARSER_STATE_DICTIONARY_FOUND_VALUE)
		{
			if (is_empty_character(character))
			{
				continue;
			}
			else if (character == ',')
			{
				parseData->state = PARSER_STATE_DICTIONARY_FOUND_VALUE_SEPARATOR;
				continue;
			}
			else if (character == '}')
			{
				magicArrayRemoveItemByIndex(&parserStack, parseStackIndex);
				continue;
			}
			else
			{
				_magicDictionary_unexpectedSymbol(executeResult, currentCharacterNumber);
				break;
			}
		}
		else if (parseData->state == PARSER_STATE_DICTIONARY_FOUND_VALUE_SEPARATOR)
		{
			if (is_empty_character(character))
			{
				continue;
			}
			else if (character == '"')
			{
				_magicDictionary_readJsonString(jsonUTF8Data, dataLength, &i, &currentCharacterNumber, keyString, executeResult);
				if (executeResultIsFailed(executeResult)) {
					break;
				}
				
				parseData->state = PARSER_STATE_DICTIONARY_LOOKING_FOR_KEY_VALUE_SEPARATOR;
				continue;
			}
			else
			{
				_magicDictionary_unexpectedSymbol(executeResult, currentCharacterNumber);
				break;
			}
		}
		else if (parseData->state == PARSER_STATE_ARRAY || parseData->state == PARSER_STATE_ARRAY_FOUND_VALUE_SEPARATOR)
		{
			if (is_empty_character(character))
			{
				continue;
			}
			else if (character == '"')
			{
				_magicDictionary_readJsonString(jsonUTF8Data, dataLength, &i, &currentCharacterNumber, valueString, executeResult);
				if (executeResultIsFailed(executeResult)) {
					break;
				}
				
				STRING* string = magicArrayAddItem(&dictionary->stringValues);
				stringInitializeWithCopy(string, valueString);
				
				MAGIC_DICTIONARY_ELEMENT* element = magicArrayAddItem(parseData->array.array);
				element->type = MAGIC_DICTIONARY_ELEMENT_TYPE_STRING;
				element->stringValue = string;
				
				parseData->state = PARSER_STATE_ARRAY_FOUND_VALUE;
				continue;
			}
			else if ((character >= '0' && character <= '9') || (character == '.') || (character == '-'))
			{
				_magicDictionary_readJsonNumber(jsonUTF8Data, dataLength, &i, &currentCharacterNumber, &valueNumber, executeResult);
				if (executeResultIsFailed(executeResult)) {
					break;
				}
				
				MAGIC_DICTIONARY_ELEMENT* element = magicArrayAddItem(parseData->array.array);
				switch (valueNumber.type)
				{
					case SF_JSON_NUMBER_TYPE_INTEGER:
						element->type = MAGIC_DICTIONARY_ELEMENT_TYPE_LONG;
						element->longValue = valueNumber.integerValue;
						break;
					
					case SF_JSON_NUMBER_TYPE_DOUBLE:
						element->type = MAGIC_DICTIONARY_ELEMENT_TYPE_DOUBLE;
						element->doubleValue = valueNumber.doubleValue;
						break;
						
					default:
						assert(0);
						break;
				}
				
				parseData->state = PARSER_STATE_ARRAY_FOUND_VALUE;
				continue;
			}
			else if (character == '{')
			{
				parseData->state = PARSER_STATE_ARRAY_FOUND_VALUE;
				
				// dictionary->dictionaryValue not parseData->dictionary.dictionary->dictionaryValues !!!
				MAGIC_DICTIONARY* value = magicArrayAddItem(&dictionary->dictionaryValues);
				magicDictionaryInitialize(value);
				
				MAGIC_DICTIONARY_ELEMENT* element = magicArrayAddItem(parseData->array.array);
				element->type = MAGIC_DICTIONARY_ELEMENT_TYPE_DICTIONARY;
				element->dictionaryValue = value;
				
				parseData = magicArrayAddItem(&parserStack);
				parseData->state = PARSER_STATE_DICTIONARY;
				parseData->dictionary.dictionary = value;
				
				continue;
			}
			else if (character == '[')
			{
				parseData->state = PARSER_STATE_ARRAY_FOUND_VALUE;
				
				// dictionary->dictionaryValue not parseData->dictionary.dictionary->arrayValues !!!
				MAGIC_ARRAY* value = magicArrayAddItem(&dictionary->arrayValues);
				magicArrayInitialize(value, sizeof(MAGIC_DICTIONARY_ELEMENT), 2);
				
				MAGIC_DICTIONARY_ELEMENT* element = magicArrayAddItem(parseData->array.array);
				element->type = MAGIC_DICTIONARY_ELEMENT_TYPE_ARRAY;
				element->arrayValue = value;
				
				parseData = magicArrayAddItem(&parserStack);
				parseData->state = PARSER_STATE_ARRAY;
				parseData->array.array = value;
				
				continue;
			}
			else
			{
				if (parseData->state == PARSER_STATE_ARRAY_FOUND_VALUE_SEPARATOR)
				{
					_magicDictionary_unexpectedSymbol(executeResult, currentCharacterNumber);
					break;
				}
				else if (character == ']')
				{
					magicArrayRemoveItemByIndex(&parserStack, parseStackIndex);
					continue;
				}
				else
				{
					_magicDictionary_unexpectedSymbol(executeResult, currentCharacterNumber);
					break;
				}
			}
		}
		else if (parseData->state == PARSER_STATE_ARRAY_FOUND_VALUE)
		{
			if (is_empty_character(character))
			{
				continue;
			}
			else if (character == ',')
			{
				parseData->state = PARSER_STATE_ARRAY_FOUND_VALUE_SEPARATOR;
				continue;
			}
			else if (character == ']')
			{
				magicArrayRemoveItemByIndex(&parserStack, parseStackIndex);
				continue;
			}
			else
			{
				_magicDictionary_unexpectedSymbol(executeResult, currentCharacterNumber);
				break;
			}
		}
	}
	stringRelease(valueNumber.temporaryData);
	stringRelease(valueString);
	stringRelease(keyString);
	magicArrayDeinitialize(&parserStack);
}
