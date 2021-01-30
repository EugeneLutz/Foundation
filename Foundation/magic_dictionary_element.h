//
//  magic_dictionary_element.h
//  Foundation
//
//  Created by Евгений Лютц on 09.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef magic_dictionary_element_h
#define magic_dictionary_element_h

#include "private_interface.h"

typedef void (* MAGIC_DICTIONARY_CUSTOM_ELEMENT_SERIALIZER_FUNC)(void* data, MAGIC_DICTIONARY* dictionary);
typedef void (* MAGIC_DICTIONARY_CUSTOM_ELEMENT_DEALLOCATOR_FUNC)(void* data, MAGIC_DICTIONARY* dictionary);

typedef struct MAGIC_DICTIONARY_CUSTOM_ELEMENT
{
	void* data;
	MAGIC_DICTIONARY_CUSTOM_ELEMENT_SERIALIZER_FUNC serializerFunc;
	MAGIC_DICTIONARY_CUSTOM_ELEMENT_DEALLOCATOR_FUNC deallocatorFunc;
}
MAGIC_DICTIONARY_CUSTOM_ELEMENT;

typedef struct MAGIC_DICTIONARY_ELEMENT
{
	MAGIC_DICTIONARY_ELEMENT_TYPE type;
	unsigned int userFlags;
	
	union
	{
		signed char charValue;
		unsigned char ucharValue;
		signed short shortValue;
		unsigned short ushortValue;
		signed int intValue;
		unsigned int uintValue;
		signed long longValue;
		unsigned long ulongValue;
		float floatValue;
		double doubleValue;
		STRING* stringValue;				// Access: MAGIC_DICTIONARY.stringValues
		MAGIC_ARRAY* arrayValue;			// Access: MAGIC_DICTIONARY.arrayValues
		MAGIC_DICTIONARY* dictionaryValue;	// Access: MAGIC_DICTIONARY.dictionaryValues
		//MAGIC_DICTIONARY_CUSTOM_ELEMENT* customValue;
		void* customValue;
	};
}
MAGIC_DICTIONARY_ELEMENT;

typedef struct MAGIC_DICTIONARY_KEY_VALUE_PAIR
{
	STRING key;
	MAGIC_DICTIONARY_ELEMENT value;
}
MAGIC_DICTIONARY_KEY_VALUE_PAIR;

#endif /* magic_dictionary_element_h */
