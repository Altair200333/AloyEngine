#pragma once
#include "Component.h"
#include "DebugGui.h"
#include "DebugGuiDrawable.h"
#include "Vector3.h"

class PointLight final: public Component, DebugGuiDrawable
{
public:
	void onDebugGuiDraw() override
	{
		DebugGui::colorPick("color", color);
		DebugGui::dragVector3("position", position);
	}
	Vector3 color{1,1,1};
	Vector3 position{};
};
