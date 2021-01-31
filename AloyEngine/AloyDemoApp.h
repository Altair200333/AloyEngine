#pragma once
#include "Application.h"
#include "CameraController.h"
#include "MeshLoader.h"
#include "OpenGLSceneRenderer.h"
#include "PointLight.h"
#include "Scene.h"

class AloyDemoApp final: public Application, public ImGuiEventSubscriber
{
	std::shared_ptr<ImGuiLayer> debugGui = std::make_shared<ImGuiLayer>();
	std::shared_ptr<OpenGLSceneRenderer> sceneRenderer = std::make_shared<OpenGLSceneRenderer>();
public:
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	
	std::shared_ptr<Object> createCamera() const
	{
		std::shared_ptr<Object> object = std::make_shared<Object>();
		object->addComponent(std::make_shared<Camera>());
		object->addComponent(std::make_shared<Transform>());
		object->addComponent(std::make_shared<CameraController>());
		return object;
	}
	std::shared_ptr<Object> createPointLight(const Vector3& pos)
	{
		std::shared_ptr<Object> object = std::make_shared<Object>();
		object->addComponent(std::make_shared<Transform>(pos));
		object->addComponent(std::make_shared<PointLight>());
		return object;
	}
	AloyDemoApp()
	{
		sceneRenderer->assignScene(scene);
		Engine::addRenderLayer(sceneRenderer);
		Engine::addRenderLayer(debugGui);

		scene->camera = createCamera();
		
		auto models = MeshLoader().loadModel("E:\\work\\blender\\suz1.fbx");
		for(auto& model: models)
		{
			std::shared_ptr<Object> object = std::make_shared<Object>();
			object->addComponent(model.mesh);
			object->addComponent(model.material);
			object->addComponent(std::make_shared<MeshRenderer>());
			object->getComponent<MeshRenderer>()->init();
			scene->addObject(object);
		}
		
		scene->addLight(createPointLight({ 1,-1.2,1.1 }));
		scene->addLight(createPointLight({ -1,-1.2,1.1 }));
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

		scene->onDebugGuiDraw();
	}
};