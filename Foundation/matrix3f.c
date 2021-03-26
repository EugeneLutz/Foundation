//
//  matrix3f.c
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

#if defined(__APPLE__) && __APPLE__

//

#else

matrix3f matrix3fFromQuaternionf(quaternionf quaternion)
{
	vector4f q = vector4fFromQuaternionf(quaternion);
	const float qxx = q.x * q.x;
	const float qxy = q.x * q.y;
	const float qxz = q.x * q.z;
	const float qxw = q.x * q.w;
	const float qyy = q.y * q.y;
	const float qyz = q.y * q.z;
	const float qyw = q.y * q.w;
	const float qzz = q.z * q.z;
	const float qzw = q.z * q.w;

	const float xx = 1 - 2 * (qyy + qzz);
	const float xy = 2 * (qxy - qzw);
	const float xz = 2 * (qxz + qyw);

	const float yx = 2 * (qxy + qzw);
	const float yy = 1 - 2 * (qxx + qzz);
	const float yz = 2 * (qyz - qxw);

	const float zx = 2 * (qxz - qyw);
	const float zy = 2 * (qyz + qxw);
	const float zz = 1 - 2 * (qxx + qyy);
	
	return matrix3fCreateWithRowComponents(xx, xy, xz,
										   yx, yy, yz,
										   zx, zy, zz);
}

#endif

matrix3f matrix3fFromMatrix4f(matrix4f matrix)
{
	vector3f c0 = matrix4fGetColumn0(matrix).xyz;
	vector3f c1 = matrix4fGetColumn1(matrix).xyz;
	vector3f c2 = matrix4fGetColumn2(matrix).xyz;
	return matrix3fCreateWithColumns(c0, c1, c2);
}

matrix3f matrix3fOrthogonalRightHand(float width, float height)
{
	const float xs = 2 / width;
	const float ys = 2 / height;
	return matrix3fCreateWithRowComponents(xs, 0,  0,
										   0,  ys, 0,
										   0,  0,  1);
}

matrix3f matrix3fTranslation(float tx, float ty)
{
	return matrix3fCreateWithRowComponents(1, 0, tx,
										   0, 1, ty,
										   0, 0, 1);
}

matrix3f matrix3fRotation(float radians, vector3f axis)
{
	axis = vector3fNormalize(axis);
	const float ct = cosf(radians);
	const float st = sinf(radians);
	const float ci = 1 - ct;
	const float x = axis.x;
	const float y = axis.y;
	const float z = axis.z;
	
	return matrix3fCreateWithRowComponents(ct + x * x * ci, x * y * ci - z * st, x * z * ci + y * st,
										   y * x * ci + z * st, ct + y * y * ci, y * z * ci - x * st,
										   z * x * ci - y * st, z * y * ci + x * st, ct + z * z * ci);
}

matrix3f matrix3fFromAxesVectors3f(vector3f x, vector3f y, vector3f z)
{
	return matrix3fCreateWithRowComponents(x.x, x.y, x.z,
										   y.x, y.y, y.z,
										   z.x, z.y, z.z);
}
