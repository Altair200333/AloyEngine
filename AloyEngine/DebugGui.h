#pragma once
#include <string>


#include "ImGuiSeedGenerator.h"
#include "Vector3.h"
#include "imgui/imgui.h"

class DebugGui
{
public:
	static void beginWindow(const std::string& name)
	{
		ImGui::Begin(name.c_str());
	}
	static void colorPick(const std::string& label, Vector3& color)
	{
		ImGui::PushID(ImGuiSeedGenerator::nextSeed());
		ImGui::ColorEdit3(label.c_str(), reinterpret_cast<float*>(&color));
		ImGui::PopID();
	}
	static void dragVector3(const std::string& label, Vector3& vector, float speed = 0.1f)
	{
		ImGui::PushID(ImGuiSeedGenerator::nextSeed());
		ImGui::DragFloat3(label.c_str(), reinterpret_cast<float*>(&vector), speed);
		ImGui::PopID();
	}
	static void endWindow()
	{
		ImGui::End();
	}
};
