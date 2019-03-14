#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "HelperFunctions.h"
#include "OpenGLLoader.h"
#include "Timer.h"
#include "Mesh.h"
#include "Square.h"
#include "Shader.h"
#include "Texture.h"

///globals
//screen
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

//shaders

const char* vertex_shader =
"#version 330 core\n"
"layout(location = 0) in vec3 vp;"
"layout(location = 1) in vec3 col;"
"out vec3 colour;"
"void main() {"
"  gl_Position = vec4(vp, 1.0);"
"  colour = col;"
"}";

const char* fragment_shader =
"#version 330 core\n"
"in vec3 colour;"
"out vec4 frag_colour;"
"void main() {"
"  frag_colour = vec4(colour, 1.0);"
"}";
///globals


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void onWindowResizeCallback(GLFWwindow* window, int width, int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	glViewport(0, 0, width, height);
}

int main(char** argv, int argc)
{
	stbi_set_flip_vertically_on_load(true);
	OpenGLLoader* instance;
	///test glm included correctly
	glm::mat4 identity(1.0f);
	glm::mat4 world;
	glm::mat4 view;

	world = glm::translate(world, glm::vec3(0, 0, -10));
	view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	///test glm included correctly

	instance = OpenGLLoader::Instance();
	instance->setWindowSize(800, 600);

	if (!instance->initialiseOpenGL())
	{
		//error occurred...
		glfwTerminate();
		printLine("Window creation failed.");
		return -1;
	}

	instance->setWindowResizeEvent(onWindowResizeCallback);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	Shader colShader("shader.vs", "shader.fs");
	Shader textureShader("coltex-shader.vs", "coltex-shader.fs");

	Mesh triangle;
	
	Vertex triVertices[3];
	triVertices[0].pos = glm::vec3(-0.5f, -0.5f, 0);
	triVertices[1].pos = glm::vec3(0.5f, -0.5f, 0);
	triVertices[2].pos = glm::vec3(0, 0.5f, 0);

	triangle.setVertices(triVertices, 3);

	int indices[3];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	triangle.setIndices(indices, 3);

	std::cout << "Triangle Info" << std::endl;
	std::cout << "Vert count: " << triangle.VertexCount() << std::endl;
	std::cout << "Index count: " << triangle.IndexCount() << std::endl;
	std::cout << "Triangle count: " << triangle.TriangleCount() << std::endl;

	Mesh rectangle;
	rectangle.useTriangleStrip();

	Vertex rectangleVerts[4];
	//tri strip arrangement
	rectangleVerts[0].pos = glm::vec3(-0.5f, -0.5f, 0);
	rectangleVerts[0].colour = Colour::Blue();
	rectangleVerts[1].pos = glm::vec3(0.5f, -0.5f, 0);
	rectangleVerts[1].colour = Colour::Blue();
	rectangleVerts[2].pos = glm::vec3(-0.5f, 0.5f, 0);
	rectangleVerts[3].pos = glm::vec3(0.5f, 0.5f, 0);

	rectangle.setVertices(rectangleVerts, 4);

	int rectIndices[4];
	rectIndices[0] = 2;
	rectIndices[1] = 0;
	rectIndices[2] = 1;
	rectIndices[3] = 3;
	rectangle.setIndices(rectIndices, 4);

	std::cout << "\nRectangle Info" << std::endl;
	std::cout << "Vert count: " << rectangle.VertexCount() << std::endl;
	std::cout << "Index count: " << rectangle.IndexCount() << std::endl;
	std::cout << "Triangle count: " << rectangle.TriangleCount() << std::endl;

	
	//startup the timer
	Timer::tick();
	int clearConsolePerFrame = 10;

	Square square;

	Texture containerTexture("container.jpg");

	while (!glfwWindowShouldClose(instance->getWindow()))
	{
		//calculate timing variables
		Timer::tick();
		//--clearConsolePerFrame;
		//if (clearConsolePerFrame <= 0)
		//{
		//	system("CLS"); //this is terrabad... don't use it
		//	clearConsolePerFrame = 10;
		//}
		//
		//printLine("deltaTime: " + std::to_string(Timer::DeltaTime()));
		//check input
		processInput(instance->getWindow());

		//render stuff
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glUseProgram(shader_programme);
		//bind
		//colShader.use();
		textureShader.use();
		containerTexture.use();

		//draw
		square.draw();
		

		//check for events and swap render buffers
		glfwSwapBuffers(instance->getWindow());
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}