#pragma once
#include <vector>


#include "DebugGui.h"
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
		DebugGui::beginWindow("Scene");

		for(int i=0; i < objects.size(); ++i)
		{
			auto& object = objects[i];
			if (ImGui::CollapsingHeader(("Object" + std::to_string(i)).c_str()))
			{
				for(auto iterator = object->componentsBegin(), end = object->componentsEnd(); iterator != end; ++iterator)
				{
					if(auto drawable = std::dynamic_pointer_cast<DebugGuiDrawable>(iterator->second); drawable != nullptr)
					{
						drawable->onDebugGuiDraw();
					}
					
				}
			}
		}
		for (int i = 0; i < lights.size(); ++i)
		{
			if (ImGui::CollapsingHeader(("light" + std::to_string(i)).c_str()))
			{
				lights[i]->getComponent<PointLight>()->onDebugGuiDraw();
			}
		}
		DebugGui::endWindow();
	}
};
