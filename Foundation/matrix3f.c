//
//  matrix3f.c
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"


#if defined(__APPLE__) && __APPLE__

matrix_float3x3 matrix3fTranslation(float tx, float ty)
{
	return (matrix_float3x3) {{
		{ 1,   0, 0 },
		{ 0,   1, 0 },
		{ tx, ty, 1 }
	}};
}

matrix_float3x3 matrix3fRotation(float radians, vector_float3 axis)
{
	axis = vector_normalize(axis);
	float ct = cosf(radians);
	float st = sinf(radians);
	float ci = 1 - ct;
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	
	return (matrix_float3x3) {{
		{     ct + x * x * ci, y * x * ci + z * st, 0 },
		{ x * y * ci - z * st,     ct + y * y * ci, 0 },
		{                   0,                   0, 1 }
	}};
}

matrix_float3x3 matrix3fOrthogonalRightHand(float width, float height)
{
	float xs = 2 / width;
	float ys = 2 / height;
	
	return (matrix_float3x3) {{
		{ xs,  0, 0 },
		{  0, ys, 0 },
		{  0,  0, 1 }
	}};
}

#else

#endif
