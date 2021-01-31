#pragma once
#include "CameraContext.h"

struct RenderContext final
{
	CameraContext cameraContext;
	std::vector<std::shared_ptr<Object>>& lights;
};
