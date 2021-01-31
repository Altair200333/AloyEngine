#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"
#include "Vector3.h"

class Transform: public Component
{
public:
	glm::mat4 transform = glm::mat4(1.0f);
	Vector3 position;
	explicit Transform(Vector3 pos = Vector3()):position(pos)
	{}
};