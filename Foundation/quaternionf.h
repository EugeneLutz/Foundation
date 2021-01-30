//
//  quaternionf.h
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef quaternionf_h
#define quaternionf_h

#include "foundation.h"

#if defined(__APPLE__) && __APPLE__

#include <simd/simd.h>
typedef simd_quatf quaternionf;

#else

typedef union quaternionf
{
	vector4f vector;
	struct {
		float x;
		float y;
		float z;
		float w;
	};
}
quaternionf;

#endif

#endif /* quaternionf_h */
