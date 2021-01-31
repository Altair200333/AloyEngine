#pragma once
#include <vector>
#include "Object.h"

class Scene
{
public:
	std::vector<std::shared_ptr<Object>> objects;
	std::shared_ptr<Object> camera;
	void addObject(std::shared_ptr<Object> object)
	{
		objects.push_back(std::move(object));
	}
};
