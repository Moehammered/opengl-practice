#ifndef SHADER__H_
#define SHADER__H_

#include <string>

class Shader
{
public:
	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
	~Shader();

	unsigned int ID();
	void use();

	void setBool(std::string paramName, bool value);
	void setFloat(std::string paramName, float value);
	void setInt(std::string paramName, int value);
	/*template <class ParamType>
	void setParameter(const std::string paramName, ParamType value);*/

private:
	unsigned int shaderID;

	void compile(std::string vertexShader, std::string fragmentShader);
};

#endif
