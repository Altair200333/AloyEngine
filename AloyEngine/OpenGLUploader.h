#pragma once
#include <memory>
#include "Shader.h"
#include "Material.h"
#include "PointLight.h"

template<typename T>
class OpenGlUploader final
{
public:
	static void upload(std::shared_ptr<T> object, Shader& shader)
	{
		Logger::log("Ahtung! cant upload");
	}
};

inline void uploadTextureSet(const std::vector<Texture>& textures, int& textureNumber, Shader& shader)
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + textureNumber); // active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		
		std::string name = textures[i].type;
		std::string number = std::to_string(i);

		// now set the sampler to the correct texture unit
		shader.setInt((name + "[" + number + "]").c_str(), textureNumber);
		++textureNumber;
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
}
template<>
class OpenGlUploader<Material>
{
public:
	static void upload(const std::shared_ptr<Material>& material, Shader& shader)
	{
		int textureNumber = 0;
		uploadTextureSet(material->diffuse, textureNumber, shader);
		uploadTextureSet(material->specular, textureNumber, shader);
		uploadTextureSet(material->normal, textureNumber, shader);
		uploadTextureSet(material->height, textureNumber, shader);
		shader.setInt("albedoCount", material->diffuse.size());
		shader.setInt("specularCount", material->specular.size());
		shader.setInt("normalCount", material->normal.size());

		shader.setVec3("objectColor", material->albedoColor);
	}
};

template<>
class OpenGlUploader<CameraContext>
{
public:
	static void upload(const CameraContext& context, Shader& shader)
	{
		shader.setVec3("viewPos", context.transform->position);
		const glm::mat4 projection = glm::perspective(glm::radians(context.camera->fov),
			static_cast<float>(Window::width()) / static_cast<float>(Window::height()), 0.1f, 100.0f);

		const glm::mat4 view = context.camera->GetViewMatrix();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		shader.setMat4("model", context.transform->transform);
	}
};

template<>
class OpenGlUploader<PointLight>
{
public:
	static void upload(const std::shared_ptr<PointLight>& light, const std::shared_ptr<Transform>& transform, int id, Shader& shader)
	{
		shader.setVec3("lights[" + std::to_string(id) + "].lightPos", transform->position);
		shader.setVec3("lights[" + std::to_string(id) + "].lightColor", light->color);
	}
	static void upload(std::vector<std::shared_ptr<Object>>& lights, Shader& shader)
	{
		for(int i=0;i<lights.size();++i)
		{
			auto pointLight = lights[i]->getComponent<PointLight>();
			auto transform = lights[i]->getComponent<Transform>();
			upload(pointLight, transform, i, shader);
		}
		shader.setInt("pointLightCount", lights.size());
	}
};