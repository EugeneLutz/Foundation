//
//  buffer_reader.h
//  Foundation
//
//  Created by Евгений Лютц on 01.01.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#ifndef buffer_reader_h
#define buffer_reader_h

#include "foundation.h"

typedef struct BUFFER_READER
{
	BUFFER* buffer;
	unsigned long editorPosition;
}
BUFFER_READER;

#endif /* buffer_reader_h */
