//
//  quaternionf.c
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

quaternionf quaternionfFromEulerVector3f(vector3f euler)
{
	float cx = cosf(euler.x / 2.f);
	float cy = cosf(euler.y / 2.f);
	float cz = cosf(euler.z / 2.f);
	float sx = sinf(euler.x / 2.f);
	float sy = sinf(euler.y / 2.f);
	float sz = sinf(euler.z / 2.f);

	const float w = cx * cy * cz + sx * sy * sz;
	const float x = sx * cy * cz - cx * sy * sz;
	const float y = cx * sy * cz + sx * cy * sz;
	const float z = cx * cy * sz - sx * sy * cz;

	return quaternionfCreate(x, y, z, w);
}
