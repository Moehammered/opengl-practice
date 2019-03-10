#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "HelperFunctions.h"
#include "OpenGLLoader.h"
#include "Timer.h"
#include "Mesh.h"

///globals
//screen
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

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

	Mesh triangle;
	
	glm::vec3 verts[3];
	verts[0] = glm::vec3(-0.5f, -0.5f, 0);
	verts[1] = glm::vec3(0.5f, -0.5f, 0);
	verts[2] = glm::vec3(0, 0.5f, 0);
	triangle.setVertices(verts, 3);

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
	
	glm::vec3 rectVerts[4]; //tri strip
	rectVerts[0] = glm::vec3(-0.5f, -0.5f, 0);
	rectVerts[1] = glm::vec3(0.5f, -0.5f, 0);
	rectVerts[2] = glm::vec3(-0.5f, 0.5f, 0);
	rectVerts[3] = glm::vec3(0.5f, 0.5f, 0);
	rectangle.setVertices(rectVerts, 4);

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
		glClear(GL_COLOR_BUFFER_BIT);

		//check for events and swap render buffers
		glfwSwapBuffers(instance->getWindow());
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}