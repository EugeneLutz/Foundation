//
//  vector3f.c
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

vector3f vector3fEulerZXYFromQuaternion(quaternionf quaternion)
{
	// https://stackoverflow.com/questions/15022630/how-to-calculate-the-angle-from-rotation-matrix
	// https://www.gregslabaugh.net/publications/euler.pdf
	
	// Resource
	// https://www.geometrictools.com/Documentation/EulerAngles.pdf
	
	matrix3f mat = matrix3fFromQuaternionf(quaternion);
	const float r00 = matrix3f_v00(mat);
	const float r01 = matrix3f_v01(mat);
	const float r02 = matrix3f_v02(mat);
	const float r10 = matrix3f_v10(mat);
	const float r11 = matrix3f_v11(mat);
	const float r12 = matrix3f_v12(mat);
	//const float r20 = matrix3f_v20(mat);
	//const float r21 = matrix3f_v21(mat);
	const float r22 = matrix3f_v22(mat);
	
	if (r12 < 1.0f)
	{
		if (r12 > -1.0f)
		{
			const float thetaX = asinf(-r12);
			const float thetaY = atan2f(r02, r22);
			const float thetaZ = atan2f(r10, r11);
			return vector3fCreate(thetaX, thetaY, thetaZ);
		}
		
		const float thetaX = M_PI_2;
		const float thetaY = -atan2f(r01, r00);
		const float thetaZ = 0.0f;
		return vector3fCreate(thetaX, thetaY, thetaZ);
	}
	
	const float thetaX = -M_PI_2;
	const float thetaY = atan2f(-r01, r00);
	const float thetaZ = 0.0f;
	return vector3fCreate(thetaX, thetaY, thetaZ);
}

vector3f vector3fEulerYXZFromQuaternion(quaternionf quaternion)
{
	matrix3f mat = matrix3fFromQuaternionf(quaternion);
	const float r00 = matrix3f_v00(mat);
	const float r01 = matrix3f_v01(mat);
	const float r02 = matrix3f_v02(mat);
	//const float r10 = matrix3f_v10(mat);
	const float r11 = matrix3f_v11(mat);
	//const float r12 = matrix3f_v12(mat);
	const float r20 = matrix3f_v20(mat);
	const float r21 = matrix3f_v21(mat);
	const float r22 = matrix3f_v22(mat);
	
	if (r21 < 1.0f)
	{
		if (r21 > -1.0f)
		{
			const float thetaX = asinf(r21);
			const float thetaY = atan2f(-r01, r11);
			const float thetaZ = atan2f(-r20, r22);
			return vector3fCreate(thetaX, thetaY, thetaZ);
		}
		
		const float thetaX = -M_PI_2;
		const float thetaY = -atan2f(r02, r00);
		const float thetaZ = 0.0f;
		return vector3fCreate(thetaX, thetaY, thetaZ);
	}
	
	const float thetaX = M_PI_2;
	const float thetaY = atan2f(r02, r00);
	const float thetaZ = 0.0f;
	return vector3fCreate(thetaX, thetaY, thetaZ);
}
