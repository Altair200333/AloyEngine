#pragma once
#include <vector>

#include "Component.h"
#include "DebugGuiDrawable.h"
#include "Texture.h"
#include "Vector3.h"

class Material final: public Component, public DebugGuiDrawable
{
public:
	std::vector<Texture> diffuse;
	std::vector<Texture> specular;
	std::vector<Texture> normal;
	std::vector<Texture> height;
	
	Vector3 albedoColor;
	float specular_ = 0.1f;
	
	Material() = default;
	Material(const std::vector<Texture>& diffuse, const std::vector<Texture>& specular, const std::vector<Texture>& normal, const std::vector<Texture>& height,
		const Vector3& albedo = { 1,0.2f,0.4f })
	{
		this->diffuse = diffuse;
		this->specular = specular;
		this->normal = normal;
		this->height = height;
		this->albedoColor = albedo;
	}

	void onDebugGuiDraw() override
	{
		if(!diffuse.empty())
			DebugGui::text("Diffuse textures: " + std::to_string(diffuse.size()));
		if (!specular.empty())
			DebugGui::text("Specular textures: " + std::to_string(specular.size()));
		if (!normal.empty())
			DebugGui::text("Normal maps: " + std::to_string(normal.size()));
		if(diffuse.empty())
			DebugGui::colorPick("Albedo", albedoColor);
	}
};
