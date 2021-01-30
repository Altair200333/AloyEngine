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

	GLFWwindow* window{};

	static void initGLFW()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void createWindow(const WindowProps& props)
	{
		window = glfwCreateWindow(static_cast<int>(props.width), static_cast<int>(props.height), props.name.c_str(), nullptr, nullptr);

		if (window == nullptr)
		{
			Logger::log("Failed to create GLFW window");
			glfwTerminate();
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			Logger::log("Failed to initialize GLAD");
		}

		glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
		glfwSetKeyCallback(window, windowKeyCallback);
		glfwSetCursorPosCallback(window, windowMouseCallback);
	}
	
	bool running = true;

	static Window& instance()
	{
		static Window windowInstance{};
		return windowInstance;
	}
public:

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
	
	//return glfwWindow for needs of input
	static GLFWwindow* getGLFWwindow()
	{
		return instance().window;
	}
	
	void onUpdate() override
	{
		running = !glfwWindowShouldClose(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
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
