//
//  segment.h
//  Foundation
//
//  Created by Евгений Лютц on 29.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef segment_h
#define segment_h

#include "foundation.h"

typedef struct SEGMENT
{
	vector3f start;
	vector3f end;
	float length;
}
SEGMENT;

#endif /* segment_h */
