#pragma once
#include "Component.h"
#include "Vector3.h"

class PointLight final: public Component
{
public:
	Vector3 color{1,1,1};
};
