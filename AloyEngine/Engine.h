#pragma once
#include <string>
#include <utility>
#include "EventDispatcher.h"
#include "OnUpdateEvent.h"
#include "RenderLayersSet.h"
#include <memory>
#include "Window.h"
#include "Input.h"
#include "MouseInput.h"
#include "ImGuiLayer.h"

class Engine final
{
	RenderLayersSet renderLayers;
	
	static Engine& instance()
	{
		static Engine engine{};
		return engine;
	}
public:
	
	static void init(const std::string& windowName)
	{
		Window::init(windowName);
		Window::setKeyCallback(Input::keyStateCallback);
		Window::setMouseCallback(MouseInput::mousePosCallback);
	}
	
	static void run()
	{
		Logger::log("Engine running");

		while (Window::isRunning())
		{
			Window::updateWindow();
			Window::clear();

			instance().renderLayers.render();

			EventDispatcher::dispatch(OnUpdateEvent());
		}
	}

	static void addRenderLayer(std::shared_ptr<RenderLayer> layer)
	{
		instance().renderLayers.add(std::move(layer));
	}
};
