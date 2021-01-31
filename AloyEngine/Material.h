#pragma once
#include <vector>

#include "Component.h"
#include "Texture.h"
#include "Vector3.h"

class Material final: public Component
{
public:
	std::vector<Texture> diffuse;
	std::vector<Texture> specular;
	std::vector<Texture> normal;
	std::vector<Texture> height;
	
	Vector3 albedoColor{1,0.2f,0.4f};
	float specular_ = 0.1f;
	
	Material() = default;
	Material(const std::vector<Texture>& diffuse, const std::vector<Texture>& specular, const std::vector<Texture>& normal, const std::vector<Texture>& height)
	{
		this->diffuse = diffuse;
		this->specular = specular;
		this->normal = normal;
		this->height = height;
	}
};
