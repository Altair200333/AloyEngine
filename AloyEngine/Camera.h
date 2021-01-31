#pragma once
#include "Component.h"
#include "Vector3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object.h"

class Transform;

class Camera final : public Component
{
public:
	float yaw = -90.0f;
	float pitch = 0.0f;

	Vector3 front;
	Vector3 right;
	Vector3 up;

	float fov;

	explicit Camera(Vector3 _front = {0, 1, 0}, Vector3 _right = {1, 0, 0}, Vector3 _up = {0, 0, 1},
	                float _fov = 60): front(_front), right(_right), up(_up), fov(_fov)
	{
	}

	void updateCameraVectors()
	{
		glm::vec3 forward;
		forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		forward.z = sin(glm::radians(pitch));
		forward.y = -sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(forward);

		right = glm::normalize(glm::cross(forward, { 0, 0, 1 }));
		up = glm::normalize(glm::cross(right.toGlm(), front.toGlm()));
	}
	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix() const;
};
#include "Transform.h"

inline glm::mat4 Camera::GetViewMatrix() const
{
	Vector3& position = owner->getComponent<Transform>()->position;
	return glm::lookAt(position.toGlm(), (position + front).toGlm(), up.toGlm());
}