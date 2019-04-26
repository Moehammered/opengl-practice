#ifndef MATERIAL__H_
#define MATERIAL__H_

#include "Shader.h"
#include "Texture.h"
#include <glm\glm.hpp>
#include <string>

class Material
{
public:
	Material();
	Material(std::string vertexShaderPath, std::string fragmentShaderPath);
	Material(Shader* const preMadeShader);
	~Material();

	void setShader(Shader* const sh);
	void setTexture(Texture* const tx);
	void setTransformProperty(std::string prop, glm::mat4 transform);
	void use();

private:
	Texture* texture;
	Shader* shader;
};

#endif