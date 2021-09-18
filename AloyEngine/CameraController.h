#pragma once
#include <vector>
#include <algorithm>
#include "Component.h"
#include "Input.h"
#include "Transform.h"
#include "Camera.h"
#include "Logger.h"
#include "MouseInput.h"
#include "OnUpdateSubscriber.h"

class CameraController final : public Component, public virtual OnUpdateSubscriber
{
	//contained vector represents amount of movement in each direction
	//{right, up, forward}
	inline static const std::vector<std::pair<KeyCode::Key, Vector3>> controlBinds = {
		{KeyCode::W, {0,0,1}},
		{KeyCode::S, {0,0,-1}},
		{KeyCode::A, {-1,0,0}},
		{KeyCode::D, {1,0,0}},
		{KeyCode::Q, {0,-1,0}},
		{KeyCode::E, {0,1,0}} };
	float speed = 0.018f;
	float mouseSensitivity = 0.022f;

public:
	explicit CameraController() = default;
	bool hasMoved = false;
	bool enabled = true;
	void onUpdate() override;
};

#include "Object.h"

inline void CameraController::onUpdate()
{
	if (!enabled)
		return;
	hasMoved = false;
	auto camera = owner->getComponent<Camera>();
	auto transform = owner->getComponent<Transform>();

	if (!camera || !transform)
	{
		Logger::log("Transform and camera components are required for CameraController");
		return;
	}

	for (auto& [key, direction] : controlBinds)
	{
		if (Input::getKeyPressed(key))
		{
			hasMoved = true;
			transform->position += (camera->front * direction.z + camera->right * direction.x + camera->up * direction.y)* speed* Profiler::currentFrameTime();
		}
	}

	if (MouseInput::getMouseButton(KeyCode::MMB))
	{
		hasMoved = true;

		camera->yaw += static_cast<float>(MouseInput::dx()) * mouseSensitivity * Profiler::currentFrameTime();
		camera->pitch += static_cast<float>(MouseInput::dy()) * mouseSensitivity * Profiler::currentFrameTime();

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		camera->pitch = std::clamp(camera->pitch, -89.0f, 89.0f);

	}
	camera->updateCameraVectors();

}
