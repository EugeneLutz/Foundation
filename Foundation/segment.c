//
//  segment.c
//  Foundation
//
//  Created by Евгений Лютц on 30.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

SEGMENT segmentFromPerspectiveFrustumRightHand(vector2f viewportSize, vector2f position2d, vector3f eyePosition, vector3f eyeRotation, float fovyRadians, float nearPlane, float farPlane)
{
	//nearPlane += 5.0f;
	//farPlane -= 970.0f;
	
	// Convert screen-space coordinates to world-space coordinates using camera's frustum
	
	// 1. Calculate segment as it would go from frustum's near plane to far plane
	
	// Convert position2d in device normalized coordinates (NDC)
	vector2f screenPos;
	// WARNING! "- viewportSize.x / 2.0f" is because of Metal NDC. Maybe it's not needed for DirectX and/or OpenGL
	screenPos.x = position2d.x - viewportSize.x / 2.0f;
	screenPos.y = position2d.y - viewportSize.y / 2.0f;
	
	const float aspect = viewportSize.x / viewportSize.y;
	
	const float nearHeight = 2.0f * tanf(fovyRadians / 2.0f) * nearPlane;
    const float nearWidth = nearHeight * aspect;
	const float nearScaleFactor = nearWidth / viewportSize.x;
	vector4f start = vector4fCreate(screenPos.x * nearScaleFactor, screenPos.y * nearScaleFactor, -nearPlane, 1.0f);
	
	const float farHeight = 2.0f * tanf(fovyRadians / 2.0f) * farPlane;
    const float farWidth = farHeight * aspect;
	const float farScaleFactor = farWidth / viewportSize.x;
	vector4f end = vector4fCreate(screenPos.x * farScaleFactor, screenPos.y * farScaleFactor, -farPlane, 1.0f);
	
	// 2. Rotate calculated segment coordinates by inverse camera rotation matrix
	
	// Make inverse rotation matrix
	matrix4f rot = matrix4fIdentity();
	rot = matrix4fMul(matrix4fRotation(-eyeRotation.x, 1.0f, 0.0f, 0.0f), rot);
	rot = matrix4fMul(matrix4fRotation(-eyeRotation.y, 0.0f, 1.0f, 0.0f), rot);
	rot = matrix4fMul(matrix4fRotation(-eyeRotation.z, 0.0f, 0.0f, 1.0f), rot);
	
	start = matrix4fMulVector4f(rot, start);
	end = matrix4fMulVector4f(rot, end);
	
	// 3. Translate rotated coordinates co camera's position
	
	SEGMENT segment;
	segment.start = vector3fSum(vector4f_xyz(start), eyePosition);
	segment.end = vector3fSum(vector4f_xyz(end), eyePosition);
	
	// That's it, magic is done
	return segment;
}

SEGMENT segmentFromOrthogonalProjectionRightHand(vector2f viewportSize, vector2f position2d, vector3f eyePosition, vector3f eyeRotation, float fovyRadians, float eyeDistance, float nearPlane, float farPlane)
{
	//nearPlane += 5.0f;
	//farPlane -= 970.0f;
	
	// Convert screen-space coordinates to world-space coordinates using camera's frustum
	
	// 1. Calculate segment as it would go from frustum's near plane to far plane
	
	// Convert position2d in device normalized coordinates (NDC)
	vector2f screenPos;
	// WARNING! "- viewportSize.x / 2.0f" is because of Metal NDC. Maybe it's not needed for DirectX and/or OpenGL
	screenPos.x = position2d.x - viewportSize.x / 2.0f;
	screenPos.y = position2d.y - viewportSize.y / 2.0f;
	
	const float aspect = viewportSize.x / viewportSize.y;
	
	const float orthoHeight = 2.0f * tanf(fovyRadians / 2.0f) * (-eyeDistance);
	const float orthoWidth = orthoHeight * aspect;
	const float scaleFactor = orthoWidth / viewportSize.x;
	vector4f start = vector4fCreate(screenPos.x * scaleFactor, screenPos.y * scaleFactor, -nearPlane, 1.0f);
	vector4f end = vector4fCreate(screenPos.x * scaleFactor, screenPos.y * scaleFactor, -farPlane, 1.0f);
	
	// 2. Rotate calculated segment coordinates by inverse camera rotation matrix
	
	// Make inverse rotation matrix
	matrix4f rot = matrix4fIdentity();
	rot = matrix4fMul(matrix4fRotation(-eyeRotation.x, 1.0f, 0.0f, 0.0f), rot);
	rot = matrix4fMul(matrix4fRotation(-eyeRotation.y, 0.0f, 1.0f, 0.0f), rot);
	rot = matrix4fMul(matrix4fRotation(-eyeRotation.z, 0.0f, 0.0f, 1.0f), rot);
	
	start = matrix4fMulVector4f(rot, start);
	end = matrix4fMulVector4f(rot, end);
	
	// 3. Translate rotated coordinates co camera's position
	
	SEGMENT segment;
	segment.start = vector3fSum(vector4f_xyz(start), eyePosition);
	segment.end = vector3fSum(vector4f_xyz(end), eyePosition);
	
	// That's it, magic is done
	return segment;
}
