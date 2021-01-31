#pragma once
#include <iostream>


#include "CameraContext.h"
#include "Component.h"
#include "Shader.h"
#include "Vector3.h"
#include "FileUtils.h"
#include "Material.h"
#include "Mesh.h"
#include "Object.h"
#include "OpenGLUploader.h"

class MeshRenderer final: public Component
{
	Shader shader = Shader(FileUtils::fileContents("shader.vs"), FileUtils::fileContents("shader.fs"));
	unsigned int VAO{}, VBO{}, EBO{};
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
public:
	void genBuffers()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}

	void bindBuffers()
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex), mesh->vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int),
		             mesh->indices.data(), GL_STATIC_DRAW);
	}

	void setAttribArray()
	{
		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Normal)));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, TexCoords)));
	}

	void init()
	{
		mesh = owner->getComponent<Mesh>();
		material = owner->getComponent<Material>();
		genBuffers();

		bindBuffers();

		setAttribArray();

		glBindVertexArray(0);
	}

	
	void render(const CameraContext& context)
	{
		shader.use();
		shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		
		shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		shader.setVec3("lightPos", Vector3{1,1,1});
		
		OpenGlUploader<CameraContext>::upload(context, shader);
		OpenGlUploader<Material>::upload(material, shader);
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
	}
};
