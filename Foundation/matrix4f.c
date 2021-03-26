//
//  matrix4f.c
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

/*
 
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

/*
 Inverse matrix:
 https://mathworld.wolfram.com/MatrixInverse.html
 */

#if defined(__APPLE__) && __APPLE__

//

#else

matrix4f matrix4fFromQuaternionf(quaternionf quaternion)
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
	
	return matrix4fCreateWithRowComponents(xx, xy, xz, 0,
										   yx, yy, yz, 0,
										   zx, zy, zz, 0,
										   0,  0,  0,  1);
}

#endif

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


matrix4f matrix4fRotation(float radians, float x, float y, float z)
{
	vector3f axis = vector3fNormalize(vector3fCreate(x, y, z));
	const float ct = cosf(radians);
	const float st = sinf(radians);
	const float ci = 1 - ct;
	x = axis.x;
	y = axis.y;
	z = axis.z;
	
	return (matrix4f) {{
		{     ct + x * x * ci, y * x * ci + z * st, z * x * ci - y * st, 0 },
		{ x * y * ci - z * st,     ct + y * y * ci, z * y * ci + x * st, 0 },
		{ x * z * ci + y * st, y * z * ci - x * st,     ct + z * z * ci, 0 },
		{                   0,                   0,                   0, 1 }
	}};
}

matrix4f matrix4fRotationX(float radians)
{
	const float ct = cosf(radians);
	const float st = sinf(radians);
	return matrix4fCreateWithRowComponents(1, 0,   0,  0,
										   0, ct, -st, 0,
										   0, st,  ct, 0,
										   0, 0,   0,  1);
}

matrix4f matrix4fRotationY(float radians)
{
	const float ct = cosf(radians);
	const float st = sinf(radians);
	return matrix4fCreateWithRowComponents(ct, 0, st, 0,
										   0,  1, 0,  0,
										  -st, 0, ct, 0,
										   0,  0, 0,  1);
}

matrix4f matrix4fRotationZ(float radians)
{
	const float ct = cosf(radians);
	const float st = sinf(radians);
	return matrix4fCreateWithRowComponents(ct, -st, 0, 0,
										   st,  ct, 0, 0,
										   0,   0,  1, 0,
										   0,   0,  0, 1);
}

matrix4f matrix4fRotationFromVector3f(float radians, vector3f axis)
{
	axis = vector3fNormalize(axis);
	const float ct = cosf(radians);
	const float st = sinf(radians);
	const float ci = 1 - ct;
	const float x = axis.x;
	const float y = axis.y;
	const float z = axis.z;
	
	return matrix4fCreateWithRowComponents(ct + x * x * ci, x * y * ci - z * st, x * z * ci + y * st, 0,
										   y * x * ci + z * st, ct + y * y * ci, y * z * ci - x * st, 0,
										   z * x * ci - y * st, z * y * ci + x * st, ct + z * z * ci, 0,
										   0, 0, 0, 1);
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


matrix4f matrix4fFromAxesVectors3f(vector3f x, vector3f y, vector3f z)
{
	return matrix4fCreateWithRowComponents(x.x, x.y, x.z, 0,
										   y.x, y.y, y.z, 0,
										   z.x, z.y, z.z, 0,
										   0,   0,   0,   1);
}
