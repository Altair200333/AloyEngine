#pragma once
#include <functional>
#include <glad/glad.h>

#include "CursorModes.h"
#include "GLFW/glfw3.h"
#include "WindowProps.h"
#include "Logger.h"
#include "OnUpdateSubscriber.h"


class Window final : public OnUpdateSubscriber
{

	using KeyCallbackType = std::function<void(int, int, int)>;
	using MouseCallbackType = std::function<void(double, double)>;

	KeyCallbackType keyCallback;
	MouseCallbackType mouseCallback;
	//===---===
	WindowProps properties;
	GLFWwindow* window = nullptr;
	GLFWmonitor* monitor = nullptr;
	bool updateViewport = true;

	static void initGLFW()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void assignCallbacks() const
	{
		glfwSetWindowSizeCallback(window, resizeCallback);
		glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
		glfwSetKeyCallback(window, windowKeyCallback);
		glfwSetCursorPosCallback(window, windowMouseCallback);
	}

	void createWindow(const WindowProps& props)
	{
		properties = props;
		window = glfwCreateWindow(static_cast<int>(properties.width), static_cast<int>(properties.height), properties.name.c_str(), nullptr, nullptr);

		if (window == nullptr)
		{
			Logger::log("Failed to create GLFW window");
			glfwTerminate();
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			Logger::log("Failed to initialize GLAD");
		}
		
		monitor = glfwGetPrimaryMonitor();
		
		glfwGetWindowSize(window, &properties.width, &properties.height);
		glfwGetWindowPos(window, &properties.position[0], &properties.position[1]);

		assignCallbacks();
	}
	
	bool running = true;

	static Window& instance()
	{
		static Window windowInstance{};
		return windowInstance;
	}
	static void resizeCallback(GLFWwindow* window, int cx, int cy)
	{
		instance().updateViewport = true;
	}
	
public:
	static bool isFullscreen()
	{
		return glfwGetWindowMonitor(instance().window) != nullptr;
	}
	static void setFullScreen(bool fullscreen)
	{
		Window& inst = instance();
		if (isFullscreen() == fullscreen)
			return;

		if (fullscreen)
		{
			// backup window position and window size
			glfwGetWindowPos(inst.window, &inst.properties.position[0], &inst.properties.position[1]);
			glfwGetWindowSize(inst.window, &inst.properties.width, &inst.properties.height);

			// get resolution of monitor
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

			// switch to full screen
			glfwSetWindowMonitor(inst.window, inst.monitor, 0, 0, mode->width, mode->height, 0);
		}
		else
		{
			// restore last window size and position
			glfwSetWindowMonitor(inst.window, nullptr, inst.properties.position[0], inst.properties.position[1],
				inst.properties.width, inst.properties.height, 0);
		}
		inst.updateViewport = true;
	}
	static void init(const WindowProps& props)
	{
		instance().initGLFW();
		instance().createWindow(props);
	}
	static bool isRunning()
	{
		return instance().running;
	}
	
	static void clear()
	{
		glClearColor(0.2f, 0.2f, 0.22f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	static void setKeyCallback(KeyCallbackType callback)
	{
		instance().keyCallback = callback;
	}
	static void setMouseCallback(MouseCallbackType callback)
	{
		instance().mouseCallback = callback;
	}
	static void setCursorMode(CursorMode::Cursor mode)
	{
		glfwSetInputMode(instance().getGLFWwindow(), GLFW_CURSOR, mode);
	}
	
	//return glfwWindow for needs of Input
	static GLFWwindow* getGLFWwindow()
	{
		return instance().window;
	}
	static void updateWindow()
	{
		if (instance().updateViewport)
		{
			glViewport(0, 0, instance().properties.width, instance().properties.height);
			instance().updateViewport = false;
		}
	}
	void onUpdate() override
	{
		running = !glfwWindowShouldClose(window);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	static int width()
	{
		return instance().properties.width;
	}
	static int height()
	{
		return instance().properties.height;
	}
	~Window() override
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
private:
	
	void close() const
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		instance().properties.width = width;
		instance().properties.height = height;
		glViewport(0, 0, width, height);
	}

	static void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		instance().keyCallback(key, scancode, action);
	}
	static void windowMouseCallback(GLFWwindow* window, double xPos, double yPos)
	{
		instance().mouseCallback(xPos, yPos);
	}

};
