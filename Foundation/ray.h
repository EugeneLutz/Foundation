//
//  ray.h
//  Foundation
//
//  Created by Евгений Лютц on 18.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef ray_h
#define ray_h

#include "foundation.h"

typedef struct RAY
{
	vector3f position;		/// Position in 3D space
	vector3f orientation;	/// Normalized direction
}
RAY;

#endif /* ray_h */
