#pragma once
#include <vector>

#include "DebugGuiDrawable.h"
#include "ImGuiSeedGenerator.h"
#include "Object.h"

class Scene: public DebugGuiDrawable
{
public:
	std::vector<std::shared_ptr<Object>> objects;
	std::vector<std::shared_ptr<Object>> lights;
	std::shared_ptr<Object> camera;
	void addObject(std::shared_ptr<Object> object)
	{
		objects.push_back(std::move(object));
	}
	void addLight(std::shared_ptr<Object> object)
	{
		lights.push_back(std::move(object));
	}
	void onDebugGuiDraw() override
	{
		ImGui::Begin("Scene");

		for(int i=0; i < objects.size(); ++i)
		{
			auto material = objects[i]->getComponent<Material>();
			if(material)
			{
				if(ImGui::CollapsingHeader(("Object" + std::to_string(i)).c_str()))
				{
					ImGui::PushID(ImGuiSeedGenerator::nextSeed());
					ImGui::ColorEdit3("Albedo", reinterpret_cast<float*>(&material->albedoColor));
					ImGui::PopID();
				}
			}
		}
		for (int i = 0; i < lights.size(); ++i)
		{
			if (ImGui::CollapsingHeader(("light" + std::to_string(i)).c_str()))
			{
				auto light = lights[i]->getComponent<PointLight>();
				if (light)
				{

					ImGui::PushID(ImGuiSeedGenerator::nextSeed());
					ImGui::ColorEdit3("color", reinterpret_cast<float*>(&light->color));
					ImGui::PopID();

				}
				auto transform = lights[i]->getComponent<Transform>();
				if (transform)
				{
					ImGui::PushID(ImGuiSeedGenerator::nextSeed());
					ImGui::DragFloat3("position", reinterpret_cast<float*>(&transform->position));
					ImGui::PopID();
				}
			}
		}
		ImGui::End();
	}
};
