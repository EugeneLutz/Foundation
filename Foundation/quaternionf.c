//
//  quaternionf.c
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

quaternionf quaternionfFromEulerXYZVector3f(vector3f euler_xyz)
{
	float cx = cosf(euler_xyz.x / 2.0f);
	float cy = cosf(euler_xyz.y / 2.0f);
	float cz = cosf(euler_xyz.z / 2.0f);
	float sx = sinf(euler_xyz.x / 2.0f);
	float sy = sinf(euler_xyz.y / 2.0f);
	float sz = sinf(euler_xyz.z / 2.0f);

	const float w = cx * cy * cz + sx * sy * sz;
	const float x = sx * cy * cz - cx * sy * sz;
	const float y = cx * sy * cz + sx * cy * sz;
	const float z = cx * cy * sz - sx * sy * cz;

	return quaternionfCreate(x, y, z, w);
}

quaternionf quaternionfFromEulerZXYVector3f(vector3f euler_zxy)
{
	// xyz -> zxy
	// x -> z
	// y -> x
	// z -> y
	
	float cx = cosf(euler_zxy.x / 2.0f);
	float cy = cosf(euler_zxy.y / 2.0f);
	float cz = cosf(euler_zxy.z / 2.0f);
	float sx = sinf(euler_zxy.x / 2.0f);
	float sy = sinf(euler_zxy.y / 2.0f);
	float sz = sinf(euler_zxy.z / 2.0f);

	const float w = cz * cx * cy + sz * sx * sy;
	const float x = cz * sx * cy + sz * cx * sy;
	const float y = cz * cx * sy - sz * sx * cy;
	const float z = sz * cx * cy - cz * sx * sy;

	return quaternionfCreate(x, y, z, w);
}
