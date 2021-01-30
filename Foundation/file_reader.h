//
//  file_reader.h
//  Foundation
//
//  Created by Евгений Лютц on 25.12.2019.
//  Copyright © 2019 Eugene Lutz. All rights reserved.
//

#ifndef file_reader_h
#define file_reader_h

#include "foundation.h"

typedef struct FILE_READER
{
	SYSTEM* system;
	void* fileId;
	unsigned long size;
	unsigned long position;
	//unsigned int bufferOffset;
	//unsigned int bufferSize;
	unsigned char* buffer;
}
FILE_READER;

#endif /* file_reader_h */
