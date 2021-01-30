//
//  magic_string.h
//  Foundation
//
//  Created by Евгений Лютц on 28.02.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef magic_string_h
#define magic_string_h

#include "foundation.h"

typedef struct STRING
{
	unsigned long dataLength;		// how many bytes allocated counting terminal null
	unsigned long length;			// how many bytes is used without counting terminal null
	unsigned long numCharacters;	// how many printable characters has data ≤ length
	
	/*!
	 UTF-8 - encoded representation of string.
	 */
	char* data;
}
STRING;

#endif /* magic_string_h */
