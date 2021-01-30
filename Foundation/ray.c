//
//  ray.c
//  Foundation
//
//  Created by Евгений Лютц on 02.01.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

RAY rayFromPoints(vector3f position, vector3f secondPoint)
{
	RAY ray;
	ray.position = position;
	ray.orientation = vector3fNormalize(vector3fSub(secondPoint, position));
	return ray;
}
