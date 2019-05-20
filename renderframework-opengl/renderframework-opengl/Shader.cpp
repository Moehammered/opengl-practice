#include "Shader.h"

#include <glad\glad.h>
#include "FileLoader.h"
#include <iostream>

void printShaderError(std::string errmsg)
{
	std::cout << "Shader Compile Error" << std::endl;
	std::cout << errmsg << std::endl;
}

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	std::string vertexShader, fragmentShader;
	try
	{
		vertexShader = loadTextFile(vertexShaderPath);
		fragmentShader = loadTextFile(fragmentShaderPath);
		//std::cout << vertexShader << std::endl;
		compile(vertexShader, fragmentShader);
	}
	catch (std::exception e)
	{
		std::cout << "Failed to load VertexShader: " << vertexShaderPath << std::endl;
		std::cout << "Failed to load FragmentShader: " << fragmentShaderPath << std::endl;
	}
}

Shader::~Shader()
{
}

unsigned int Shader::ID()
{
	return shaderID;
}

void Shader::use()
{
	glUseProgram(shaderID);
}

void Shader::setBool(std::string paramName, bool value)
{
	glUniform1i(glGetUniformLocation(shaderID, paramName.c_str()), value);
}

void Shader::setFloat(std::string paramName, float value)
{
	glUniform1f(glGetUniformLocation(shaderID, paramName.c_str()), value);
}

void Shader::setInt(std::string paramName, int value)
{
	glUniform1i(glGetUniformLocation(shaderID, paramName.c_str()), value);
}

void Shader::compile(std::string vertexShader, std::string fragmentShader)
{
	GLuint vertexID, fragmentID;
	const GLchar * vS = vertexShader.c_str();
	const GLchar* fS = fragmentShader.c_str();

	int compileStatus;
	char errLog[512];

	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vS, NULL);
	glCompileShader(vertexID);
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus)
	{
		glGetShaderInfoLog(vertexID, 512, NULL, errLog);
		printShaderError(errLog);
	}

	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fS, NULL);
	glCompileShader(fragmentID);
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus)
	{
		glGetShaderInfoLog(fragmentID, 512, NULL, errLog);
		printShaderError(errLog);
	}

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexID);
	glAttachShader(shaderID, fragmentID);
	glLinkProgram(shaderID);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &compileStatus);
	if (!compileStatus)
	{
		glGetProgramInfoLog(shaderID, 512, NULL, errLog);
		printShaderError(errLog);
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}
