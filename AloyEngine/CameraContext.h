#pragma once
#include <memory>
#include "Camera.h"
#include "Transform.h"

struct CameraContext
{
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Transform> transform;
};
