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
	unsigned int VAO{}, VBO{}, EBO{};
	std::shared_ptr<Mesh> mesh;
public:
	void init()
	{
		mesh = owner->getComponent<Mesh>();
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Mesh::Vertex), mesh->vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int),
			mesh->indices.data(), GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)offsetof(Mesh::Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)offsetof(Mesh::Vertex, TexCoords));

		glBindVertexArray(0);
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

		lightingShader.setMat4("model", context.transform->transform);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};
