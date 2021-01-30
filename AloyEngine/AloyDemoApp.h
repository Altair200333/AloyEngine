#pragma once
#include "Application.h"

class AloyDemoApp final: public Application
{
	std::shared_ptr<ImGuiLayer> debugGui = std::make_shared<ImGuiLayer>();

public:
	AloyDemoApp()
	{
		Engine::addRenderLayer(debugGui);
	}
	void onUpdate() override
	{
		if (Input::getKeyDown(KeyCode::num1))
		{
			Window::setCursorMode(CursorMode::CursorNormal);
		}
		else if (Input::getKeyDown(KeyCode::num2))
		{
			Window::setCursorMode(CursorMode::CursorHidden);
		}
		else if (Input::getKeyDown(KeyCode::num3))
		{
			Window::setCursorMode(CursorMode::CursorDisabled);
		}
		if(Input::getKeyDown(KeyCode::F1))
		{
			debugGui->setEnabled(!debugGui->enabled);
		}
	}
};