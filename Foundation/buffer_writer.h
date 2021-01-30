//
//  buffer_writer.h
//  Foundation
//
//  Created by Евгений Лютц on 01.01.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#ifndef buffer_writer_h
#define buffer_writer_h

#include "private_interface.h"

typedef struct BUFFER_WRITER
{
	BUFFER* buffer;
	unsigned long editorPosition;
	unsigned long capacityIncrement;
}
BUFFER_WRITER;

#endif /* buffer_writer_h */
