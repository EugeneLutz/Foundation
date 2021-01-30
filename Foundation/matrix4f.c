//
//  matrix4f.c
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

/**
 
 * Compute the center points of the near and far planes:
 vec3 nearCenter = camPos - camForward * nearDistance;
 vec3 farCenter = camPos - camForward * farDistance;
 
 
 * Compute the widths and heights of the near and far planes:
 real nearHeight = 2 * tan(fovRadians/ 2) * nearDistance;
 real farHeight = 2 * tan(fovRadians / 2) * farDistance;
 real nearWidth = nearHeight * viewRatio;
 real farWidth = farHeight * viewRatio;
 
 
 * Compute the corner points from the near and far planes:
 vec3 farTopLeft = farCenter + camUp * (farHeight*0.5) - camRight * (farWidth*0.5);
 vec3 farTopRight = farCenter + camUp * (farHeight*0.5) + camRight * (farWidth*0.5);
 vec3 farBottomLeft = farCenter - camUp * (farHeight*0.5) - camRight * (farWidth*0.5);
 vec3 farBottomRight = farCenter - camUp * (farHeight*0.5) + camRight * (farWidth*0.5);

 vec3 nearTopLeft = nearCenter + camY * (nearHeight*0.5) - camX * (nearWidth*0.5);
 vec3 nearTopRight = nearCenter + camY * (nearHeight*0.5) + camX * (nearWidth*0.5);
 vec3 nearBottomLeft = nearCenter - camY * (nearHeight*0.5) - camX * (nearWidth*0.5);
 vec3 nearBottomRight = nearCenter - camY * (nearHeight*0.5) + camX * (nearWidth*0.5);
 
 
 * Compute each plane from any three corners of the plane, wound CW or CCW to point inward (depending on coordinate system).
 vec3 p0, p1, p2;

 p0 = nearBottomLeft; p1 = farBottomLeft; p2 = farTopLeft;
 vec3 leftPlaneNormal = Normalize(Cross(p1-p0, p2-p1));
 vec3 leftPlaneOffset = Dot(leftPlaneNormal, p0);

 p0 = nearTopLeft; p1 = farTopLeft; p2 = farTopRight;
 vec3 topPlaneNormal = Normalize(Cross(p1-p0, p2-p1));
 vec3 topPlaneNormal = Dot(topPlaneNormal , p0);

 p0 = nearTopRight; p1 = farTopRight; p2 = farBottomRight;
 vec3 rightPlaneNormal = Normalize(Cross(p1-p0, p2-p1));
 vec3 rightPlaneNormal = Dot(rightPlaneNormal , p0);

 p0 = nearBottomRight; p1 = farBottomRight; p2 = farBottomLeft;
 vec3 bottomPlaneNormal = Normalize(Cross(p1-p0, p2-p1));
 vec3 bottomPlaneNormal = Dot(bottomPlaneNormal , p0);
 
 */

matrix4f matrix4fTranslation(float tx, float ty, float tz)
{
	return matrix4fCreateWithRowComponents(1, 0, 0, tx,
										   0, 1, 0, ty,
										   0, 0, 1, tz,
										   0, 0, 0, 1);
}

matrix4f matrix4fTranslationFromVector3f(vector3f vector)
{
	const float x = vector.x;
	const float y = vector.y;
	const float z = vector.z;
	
	return matrix4fCreateWithRowComponents(1, 0, 0, x,
										   0, 1, 0, y,
										   0, 0, 1, z,
										   0, 0, 0, 1);
}


matrix4f matrix4fPerspectiveLeftHand_MetalNDC(float fovyRadians, float aspect, float nearZ, float farZ)
{
	const float ys = 1.0f / tanf(fovyRadians * 0.5f);
	const float xs = ys / aspect;
	const float zs = farZ / (farZ - nearZ);
	const float tz = -nearZ * zs;
	
	return matrix4fCreateWithRowComponents(xs, 0,  0,  0,
										   0,  ys, 0,  0,
										   0,  0,  zs, tz,
										   0,  0,  1,  0);
}

matrix4f matrix4fPerspectiveRightHand_MetalNDC(float fovyRadians, float aspect, float nearZ, float farZ)
{
	const float ys = 1.0f / tanf(fovyRadians * 0.5f);
	const float xs = ys / aspect;
	const float zs = farZ / (nearZ - farZ);
	const float tz = nearZ * zs;

	return matrix4fCreateWithRowComponents(xs, 0,  0,   0,
										   0,  ys, 0,   0,
										   0,  0,  zs, tz,
										   0,  0,  -1,  0);
}


matrix4f matrix4fOrthogonalLeftHand_MetalNDC(float left, float top, float right, float bottom, float near, float far)
{
	const float x = 2.0f / (right - left);
	const float y = 2.0f / (top - bottom);
	const float z = 1.0f / (far - near);
	const float tx = (right + left) / (left - right);
	const float ty = (top + bottom) / (bottom - top);
	const float tz = near / (near - far);
	
	return matrix4fCreateWithRowComponents(x, 0, 0, tx,
										   0, y, 0, ty,
										   0, 0, z, tz,
										   0, 0, 0, 1);
}

matrix4f matrix4fOrthogonalRightHand_MetalNDC(float left, float top, float right, float bottom, float near, float far)
{
	const float x = 2.0f / (right - left);
	const float y = 2.0f / (top - bottom);
	const float z = -1.0f / (far - near);
	const float tx = (right + left) / (left - right);
	const float ty = (top + bottom) / (bottom - top);
	const float tz = near / (near - far);
	
	return matrix4fCreateWithRowComponents(x, 0, 0, tx,
										   0, y, 0, ty,
										   0, 0, z, tz,
										   0, 0, 0, 1);
}

matrix4f matrix4fLookAtLeftHand(vector3f eye, vector3f target, vector3f up)
{
	vector3f z = vector3fNormalize(target - eye);
	vector3f x = vector3fNormalize(vector3fCross(up, z));
	vector3f y = vector3fCross(z, x);
	vector3f t = vector3fCreate(-vector3fDot(x, eye), -vector3fDot(y, eye), -vector3fDot(z, eye));
	
	return matrix4fCreateWithColumnComponents(x.x, y.x, z.x, 0,
											  x.y, y.y, z.y, 0,
											  x.z, y.z, z.z, 0,
											  t.x, t.y, t.z, 1);
}

matrix4f matrix4fLookAtRightHand(vector3f eye, vector3f target, vector3f up)
{
	vector3f z = vector3fNormalize(eye - target);
	vector3f x = vector3fNormalize(vector3fCross(up, z));
	vector3f y = vector3fCross(z, x);
	vector3f t = vector3fCreate(-vector3fDot(x, eye), -vector3fDot(y, eye), -vector3fDot(z, eye));

	return matrix4fCreateWithColumnComponents(x.x, y.x, z.x, 0,
											  x.y, y.y, z.y, 0,
											  x.z, y.z, z.z, 0,
											  t.x, t.y, t.z, 1);
}


matrix4f matrix4fRotation(float radians, vector3f axis)
{
	axis = vector3fNormalize(axis);
	float ct = cosf(radians);
	float st = sinf(radians);
	float ci = 1 - ct;
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	
	return (matrix4f) {{
		{     ct + x * x * ci, y * x * ci + z * st, z * x * ci - y * st, 0 },
		{ x * y * ci - z * st,     ct + y * y * ci, z * y * ci + x * st, 0 },
		{ x * z * ci + y * st, y * z * ci - x * st,     ct + z * z * ci, 0 },
		{                   0,                   0,                   0, 1 }
	}};
}


matrix4f matrix4fEulerTransform(float head, float pitch, float roll)
{
	const float ch = cosf(head);
	const float sh = sinf(head);
	
	const float cp = cosf(pitch);
	const float sp = sinf(pitch);
	
	const float cr = cosf(roll);
	const float sr = sinf(roll);
	
	return matrix4fCreateWithColumnComponents(cr*ch - sr*sp*sh, sr*ch + cr*sp*sh, -cp*sh, 0,
											  -sr*cp,           cr*cp,            sp,     0,
											  cr*sh + sr*sp*ch, sr*sh - cr*sp*ch, cp*ch,  0,
											  0,                0,                0,      1);
}

matrix4f matrix4fFromQuaternionf(quaternionf q1)
{
	vector4f q = vector4fFromQuaternionf(q1);
	const float xx = q.x * q.x;
	const float xy = q.x * q.y;
	const float xz = q.x * q.z;
	const float xw = q.x * q.w;
	const float yy = q.y * q.y;
	const float yz = q.y * q.z;
	const float yw = q.y * q.w;
	const float zz = q.z * q.z;
	const float zw = q.z * q.w;

	// indices are m<column><row>
	const float m00 = 1 - 2 * (yy + zz);
	const float m10 = 2 * (xy - zw);
	const float m20 = 2 * (xz + yw);

	const float m01 = 2 * (xy + zw);
	const float m11 = 1 - 2 * (xx + zz);
	const float m21 = 2 * (yz - xw);

	const float m02 = 2 * (xz - yw);
	const float m12 = 2 * (yz + xw);
	const float m22 = 1 - 2 * (xx + yy);
	
	return matrix4fCreateWithColumnComponents(m00, m01, m02, 0,
											  m10, m11, m12, 0,
											  m20, m21, m22, 0,
											  0,   0,   0,   1);
}


matrix4f matrix4fFromAxesVectors3f(vector3f x, vector3f y, vector3f z)
{
	return matrix4fCreateWithColumnComponents(x.x, y.x, z.x, 0,
											  x.y, y.y, z.y, 0,
											  x.z, y.z, z.z, 0,
											  0,   0,   0,   1);
}
