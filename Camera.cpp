#include "Camera.h"


Camera::Camera()
{
	direction = position - target;
	direction.Normalize();
	cameraRight = cyVec3f(0.0f, 1.0f, 0.0f);
	cameraRight.Cross(direction).Normalize();
	cameraUp = direction;
	cameraUp.Cross(cameraRight);
	view = cyMatrix4f::View(position, target, cameraUp);
}