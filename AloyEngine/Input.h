#pragma once
#include <GLFW/glfw3.h>
#include <map>

#include "KeyCode.h"
#include "OnUpdateSubscriber.h"
#include "Window.h"

class Input final : virtual public OnUpdateSubscriber
{
	std::map<KeyCode::Key, int> keyEvents;

	bool contains(KeyCode::Key key)
	{
		return keyEvents.find(key) != keyEvents.end();
	}

	static Input& instance()
	{
		static Input instance{};
		return instance;
	}

	Input() = default;
public:
	static void keyStateCallback(int key, int scancode, int action)
	{
		instance().keyEvents[key] = action;
	}

	static bool getKeyDown(KeyCode::Key key)
	{
		return instance().contains(key) && instance().keyEvents[key] == GLFW_PRESS;
	}
	static bool getKeyUp(KeyCode::Key key)
	{
		return instance().contains(key) && instance().keyEvents[key] == GLFW_RELEASE;
	}

	static bool getKeyPressed(KeyCode::Key key)
	{
		return glfwGetKey(Window::getGLFWwindow(), key) == GLFW_PRESS;
	}

	void onUpdate() override
	{
		instance().keyEvents.clear();
	}
};
