#pragma once
#include "RenderLayer.h"
#include <GLFW/glfw3.h>
#include "Window.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "ImGuiEvent.h"

class ImGuiLayer final : public RenderLayer
{
	bool show_demo_window = true;

	static void setParams(ImGuiIO& io)
	{
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(Window::getGLFWwindow(), true);
		ImGui_ImplOpenGL3_Init("#version 130");
	}

	static void drawContents()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

public:
	
	explicit ImGuiLayer()
	{
		bool err = gladLoadGL() == 0;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;

		setParams(io);
	}

	void onBegin() override
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void onEnd() override
	{
		drawContents();
	}

	void onDraw() override
	{
		ImGui::ShowDemoWindow(&show_demo_window);
		EventDispatcher::dispatch(ImGuiEvent());
	}

	~ImGuiLayer()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
};
