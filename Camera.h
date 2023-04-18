#pragma once

#include "cyGL/cyVector.h"
#include "cyGL/cyMatrix.h"

class Camera
{

public:
	cyVec3f position = cyVec3f(0.0f, 0.0f, 3.0f);
	cyVec3f target = cyVec3f(0.0f, 0.0f, 0.0f);
	cyVec3f cameraRight;
	cyVec3f cameraUp;
	cyVec3f direction;
	
	cyMatrix4f view;

	Camera();
};

