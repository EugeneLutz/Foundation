//
//  matrix3f.c
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

matrix3f matrix3fFromMatrix4f(matrix4f matrix)
{
	vector3f c0 = matrix4fGetColumn0(matrix).xyz;
	vector3f c1 = matrix4fGetColumn1(matrix).xyz;
	vector3f c2 = matrix4fGetColumn2(matrix).xyz;
	return matrix3fCreateWithColumns(c0, c1, c2);
}

#if defined(__APPLE__) && __APPLE__

matrix3f matrix3fTranslation(float tx, float ty)
{
	return (matrix3f) {{
		{ 1,   0, 0 },
		{ 0,   1, 0 },
		{ tx, ty, 1 }
	}};
}

matrix3f matrix3fRotation(float radians, vector_float3 axis)
{
	axis = vector_normalize(axis);
	float ct = cosf(radians);
	float st = sinf(radians);
	float ci = 1 - ct;
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	
	return (matrix3f) {{
		{     ct + x * x * ci, y * x * ci + z * st, 0 },
		{ x * y * ci - z * st,     ct + y * y * ci, 0 },
		{                   0,                   0, 1 }
	}};
}

matrix3f matrix3fOrthogonalRightHand(float width, float height)
{
	float xs = 2 / width;
	float ys = 2 / height;
	
	return (matrix3f) {{
		{ xs,  0, 0 },
		{  0, ys, 0 },
		{  0,  0, 1 }
	}};
}

#else

#endif
