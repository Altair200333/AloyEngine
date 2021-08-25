#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Component.h"
#include "DebugGuiDrawable.h"
#include "Vector3.h"

class Transform: public Component, public DebugGuiDrawable
{
public:
	glm::mat4 transform;
	Vector3 position;
	
	explicit Transform(Vector3 pos = Vector3()): position(pos)
	{
		transform = glm::identity<glm::mat4>();
	}
	
	void onDebugGuiDraw() override
	{
		const auto oldPos = position;
		DebugGui::dragVector3("Position", position);
		const auto newPos = position;
		translate(-oldPos);
		translate(newPos);
	}
	
	void translate(const Vector3& translation)
	{
		position += translation;
		auto m = glm::identity<glm::mat4>();
		m = glm::translate(m, translation.vec3());
		transform = m * transform;
	}
	void rotate(float angle, const Vector3& axis)
	{		
		rotate(glm::angleAxis(angle, axis.vec3()));
	}

	void rotate(const glm::quat& quaternion)
	{
		auto m = glm::identity<glm::mat4>();
		m = glm::translate(m, position.vec3());
		m *= glm::mat4_cast(quaternion);
		m = glm::translate(m, -position.vec3());

		transform = m * transform;
	}
	
	void rotateAround(float angle, const Vector3& axis, const Vector3& point)
	{
		const auto rotation = glm::angleAxis(angle, axis.vec3());

		auto m = glm::identity<glm::mat4>();
		m = glm::translate(m, point.vec3());
		m *= glm::mat4_cast(rotation);
		m = glm::translate(m, -point.vec3());

		position.fromGLM(m * position.vec4());

		transform = m * transform;
	}
};