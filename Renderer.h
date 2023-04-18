#pragma once

#include <vector>
#include "WorldObject.h"
#include "Camera.h"

using namespace std;

class Renderer
{

	// vector of objects in the scene
	vector<WorldObject> Objects;
	Camera camera;
};

