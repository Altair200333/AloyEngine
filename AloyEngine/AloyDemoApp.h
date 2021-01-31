#pragma once
#include "Application.h"
#include "CameraController.h"
#include "MeshLoader.h"
#include "OpenGLSceneRenderer.h"
#include "Scene.h"

class AloyDemoApp final: public Application, public ImGuiEventSubscriber
{
	std::shared_ptr<ImGuiLayer> debugGui = std::make_shared<ImGuiLayer>();
	std::shared_ptr<OpenGLSceneRenderer> sceneRenderer = std::make_shared<OpenGLSceneRenderer>();
public:
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();

	AloyDemoApp()
	{
		sceneRenderer->assignScene(scene);
		Engine::addRenderLayer(sceneRenderer);
		Engine::addRenderLayer(debugGui);

		std::shared_ptr<Object> object1 = std::make_shared<Object>();
		object1->addComponent(std::make_shared<Mesh>());
		object1->addComponent(std::make_shared<MeshRenderer>());
		object1->getComponent<MeshRenderer>()->init();
		
		scene->addObject(object1);

		std::shared_ptr<Object> object2 = std::make_shared<Object>();
		object2->addComponent(std::make_shared<Camera>());
		object2->addComponent(std::make_shared<Transform>());
		object2->addComponent(std::make_shared<CameraController>());
		scene->camera = object2;
		
		auto r = MeshLoader().loadModel("E:\\work\\blender\\suz1.fbx");
		for(auto& mesh: r)
		{
			std::shared_ptr<Object> object3 = std::make_shared<Object>();
			object3->addComponent(mesh);
			object3->addComponent(std::make_shared<MeshRenderer>());
			object3->getComponent<MeshRenderer>()->init();
			scene->addObject(object3);
		}
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
		if (Input::getKeyDown(KeyCode::R))
		{
			Window::setFullScreen(!Window::isFullscreen());
		}
	}

	void onImGuiDraw() override
	{
		ImGui::Begin("App");
		ImGui::Checkbox("Debug ui", &debugGui->enabled);
		ImGui::Checkbox("OpenGL render", &sceneRenderer->enabled);
		ImGui::End();
	}
};