#pragma once
#include <iostream>


#include "CameraContext.h"
#include "Component.h"
#include "Shader.h"
#include "Vector3.h"
#include "FileUtils.h"
#include "Mesh.h"
#include "Object.h"

class MeshRenderer final: public Component
{
	Shader lightingShader = Shader(FileUtils::fileContents("shader.vs"), FileUtils::fileContents("shader.fs"));
	unsigned int VBO, cubeVAO;
public:
	void init()
	{
		auto mesh = owner->getComponent<Mesh>();
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, mesh->data.size()*sizeof(float), mesh->data.data(), GL_STATIC_DRAW);

		glBindVertexArray(cubeVAO);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	void render(const CameraContext& context)
	{
		lightingShader.use();
		lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("lightPos", Vector3{1,1,1});
		lightingShader.setVec3("viewPos", context.transform->position);

		glm::mat4 projection = glm::perspective(glm::radians(context.camera->fov), 
			(float)Window::width() / (float)Window::height(), 0.1f, 100.0f);
		glm::mat4 view = context.camera->GetViewMatrix();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		lightingShader.setMat4("model", model);

		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
};
