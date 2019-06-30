#include "Material.h"

#include <glad\glad.h>
#include <glm\gtc\type_ptr.hpp>
#include "InterleavedVertex.h"

Material::Material()
{
	shader = new Shader("transform-coltex-shader.vs", "coltex-shader.fs");
	createDefaultAttributes();
}

Material::Material(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	shader = new Shader(vertexShaderPath, fragmentShaderPath);
	createDefaultAttributes();
}

Material::Material(Shader * const preMadeShader)
{
	shader = preMadeShader;
	createDefaultAttributes();
}


Material::~Material()
{
	delete shader;
	delete texture;
}

unsigned int Material::shaderID()
{
	return shader->ID();
}

void Material::setAttributes(const VertexAttributes * attribs, unsigned int attribCount)
{
	attributes.clear();
	attributes.insert(attributes.begin(), attribs, attribs + attribCount);
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

void Material::setIntProperty(std::string prop, int val)
{
	shader->setInt(prop, val);
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

const std::vector<VertexAttributes> Material::MaterialAttributes() const
{
	return attributes;
}

void Material::createDefaultAttributes()
{
	VertexAttributes attrib[] = {
		{
			0, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::pos))
		},
		{
			1, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::colour))
		}
	};

	attributes.insert(attributes.begin(), attrib, attrib + 2);
}
