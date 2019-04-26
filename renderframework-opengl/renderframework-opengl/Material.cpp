#include "Material.h"

#include <glad\glad.h>
#include <glm\gtc\type_ptr.hpp>

Material::Material()
{
	shader = new Shader("transform-coltex-shader.vs", "coltex-shader.fs");
}

Material::Material(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	shader = new Shader(vertexShaderPath, fragmentShaderPath);
}

Material::Material(Shader * const preMadeShader)
{
	shader = preMadeShader;
}


Material::~Material()
{
	delete shader;
	delete texture;
}

void Material::setShader(Shader * const sh)
{
	delete shader;
	shader = sh;
}

void Material::setTexture(Texture * const tx)
{
	if (texture != nullptr)
		delete texture;
	texture = tx;
}

void Material::setTransformProperty(std::string prop, glm::mat4 transform)
{
	if (shader)
	{
		unsigned int trLoc = glGetUniformLocation(shader->ID(), prop.c_str());
		glUniformMatrix4fv(trLoc, 1, GL_FALSE, glm::value_ptr(transform));
	}
}

void Material::use()
{
	if (shader)
	{
		shader->use();
		if (texture)
			texture->use();
	}
}
