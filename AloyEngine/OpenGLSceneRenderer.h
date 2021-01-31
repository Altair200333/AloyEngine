#pragma once
#include "Camera.h"
#include "MeshRenderer.h"
#include "RenderLayer.h"
#include "Scene.h"
#include "Transform.h"

class OpenGLSceneRenderer final: public RenderLayer
{
	std::shared_ptr<Scene> associatedScene;
public:

	void assignScene(std::shared_ptr<Scene> scene)
	{
		associatedScene = std::move(scene);
	}
	void onBegin() override
	{
		glEnable(GL_DEPTH_TEST);
	}
	void onEnd() override
	{
		glDisable(GL_DEPTH_TEST);
	}
	void onDraw() override
	{
		const CameraContext context{associatedScene->camera->getComponent<Camera>(), associatedScene->camera->getComponent<Transform>()};
		for(auto& object: associatedScene->objects)
		{
			auto meshRenderer = object->getComponent<MeshRenderer>();
			if(meshRenderer)
			{
				meshRenderer->render(context);
			}
		}
	}
};
