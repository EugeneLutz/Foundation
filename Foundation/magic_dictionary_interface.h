//
//  magic_dictionary_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 09.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef magic_dictionary_interface_h
#define magic_dictionary_interface_h

#include "foundation.h"

typedef struct MAGIC_DICTIONARY_ELEMENT MAGIC_DICTIONARY_ELEMENT;
//typedef struct MAGIC_DICTIONARY_KEY_VALUE_PAIR MAGIC_DICTIONARY_KEY_VALUE_PAIR;

void magicDictionaryInitializeWithContentsOfJsonFileInMainBundle(MAGIC_DICTIONARY* dictionary, SYSTEM* system, const char* name, const char* extension, EXECUTE_RESULT* executeResult);
void magicDictionaryInitialize(MAGIC_DICTIONARY* dictionary);
void magicDictionaryDeinitialize(MAGIC_DICTIONARY* dictionary);

//MAGIC_DICTIONARY_ELEMENT* magicDictionaryAddCharValueWithUTF8Name(char value, const char* utf8Name);
//MAGIC_DICTIONARY_ELEMENT* magicDictionaryAddCharValueWithName(char value, STRING* name);

void magicDictionaryReadJsonUTF8Data(MAGIC_DICTIONARY* dictionary, const char* jsonUTF8Data, const char* rootName, int dontUseRootObjectForDictionary, EXECUTE_RESULT* executeResult);
void magicDictionaryExportToJsonString(MAGIC_DICTIONARY* dictionary, STRING* outJsonString, EXECUTE_RESULT* executeResult);

MAGIC_DICTIONARY_ELEMENT* magicDictionaryGetItemWithKey(MAGIC_DICTIONARY* dictionary, const char* keyData);

MAGIC_DICTIONARY_ELEMENT_TYPE magicDictionaryElementGetType(MAGIC_DICTIONARY_ELEMENT* element);
MAGIC_ARRAY* magicDictionaryElementGetArrayValue(MAGIC_DICTIONARY_ELEMENT* element);
MAGIC_DICTIONARY* magicDictionaryElementGetDictionaryValue(MAGIC_DICTIONARY_ELEMENT* element);

int magicDictionaryGetBoolean(MAGIC_DICTIONARY* dictionary, const char* key, EXECUTE_RESULT* executeResult);
long magicDictionaryGetLong(MAGIC_DICTIONARY* dictionary, const char* key, EXECUTE_RESULT* executeResult);
float magicDictionaryGetFloat(MAGIC_DICTIONARY* dictionary, const char* key, EXECUTE_RESULT* executeResult);
STRING* magicDictionaryGetString(MAGIC_DICTIONARY* dictionary, const char* key, EXECUTE_RESULT* executeResult);
MAGIC_ARRAY* magicDictionaryGetArray(MAGIC_DICTIONARY* dictionary, const char* key, EXECUTE_RESULT* executeResult);
MAGIC_DICTIONARY* magicDictionaryGetDictionary(MAGIC_DICTIONARY* dictionary, const char* key, EXECUTE_RESULT* executeResult);
vector2f magicDictionaryGetVector2f(MAGIC_DICTIONARY* dictionary, const char* xKey, const char* yKey, EXECUTE_RESULT* executeResult);

MAGIC_DICTIONARY_ELEMENT* magicDictionaryArrayGetItem(MAGIC_ARRAY* array, unsigned long index);

MAGIC_DICTIONARY* magicDictionaryArrayGetDictionary(MAGIC_ARRAY* array, unsigned long index, EXECUTE_RESULT* executeResult);
STRING* magicDictionaryArrayGetString(MAGIC_ARRAY* array, unsigned long index, EXECUTE_RESULT* executeResult);

#endif /* magic_dictionary_interface_h */
