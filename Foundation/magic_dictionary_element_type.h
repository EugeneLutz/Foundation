//
//  magic_dictionary_element_type.h
//  Foundation
//
//  Created by Евгений Лютц on 09.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef magic_dictionary_element_type_h
#define magic_dictionary_element_type_h

typedef enum MAGIC_DICTIONARY_ELEMENT_TYPE
{
	MAGIC_DICTIONARY_ELEMENT_TYPE_CHAR = 0,
	MAGIC_DICTIONARY_ELEMENT_TYPE_UCHAR,
	MAGIC_DICTIONARY_ELEMENT_TYPE_SHORT,
	MAGIC_DICTIONARY_ELEMENT_TYPE_USHORT,
	MAGIC_DICTIONARY_ELEMENT_TYPE_INT,
	MAGIC_DICTIONARY_ELEMENT_TYPE_UINT,
	MAGIC_DICTIONARY_ELEMENT_TYPE_LONG,
	MAGIC_DICTIONARY_ELEMENT_TYPE_ULONG,
	MAGIC_DICTIONARY_ELEMENT_TYPE_FLOAT,
	MAGIC_DICTIONARY_ELEMENT_TYPE_DOUBLE,
	MAGIC_DICTIONARY_ELEMENT_TYPE_STRING,
	MAGIC_DICTIONARY_ELEMENT_TYPE_ARRAY,
	MAGIC_DICTIONARY_ELEMENT_TYPE_DICTIONARY,
	MAGIC_DICTIONARY_ELEMENT_TYPE_OTHER,
	MAGIC_DICTIONARY_ELEMENT_TYPE_NULL
}
MAGIC_DICTIONARY_ELEMENT_TYPE;

#endif /* magic_dictionary_element_type_h */
