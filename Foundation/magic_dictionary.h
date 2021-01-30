//
//  magic_dictionary.h
//  Foundation
//
//  Created by Евгений Лютц on 09.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef magic_dictionary_h
#define magic_dictionary_h

#include "foundation.h"

typedef struct MAGIC_DICTIONARY
{
	MAGIC_ARRAY elements;			// collection of MAGIC_DICTIONARY_KEY_VALUE_PAIR values
	MAGIC_ARRAY stringValues;		// collection of STRING values
	MAGIC_ARRAY arrayValues;		// collection of arrays which contain MAGIC_DICTIONARY_ELEMENT values
	MAGIC_ARRAY dictionaryValues;	// collection of MAGIC_DICTIONARY values
}
MAGIC_DICTIONARY;

#endif /* magic_dictionary_h */
