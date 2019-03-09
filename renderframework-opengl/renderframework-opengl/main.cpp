#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "HelperFunctions.h"
#include "OpenGLLoader.h"

///globals
//screen
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

//time
float lastTime = 0;
float currentTime = 0;
float deltaTime = 0;

///globals

void processTime()
{
	currentTime = (float)glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}

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

	//startup the timer
	processTime();
	int clearConsolePerFrame = 10;
	while (!glfwWindowShouldClose(instance->getWindow()))
	{
		//calculate timing variables
		processTime();
		--clearConsolePerFrame;
		if (clearConsolePerFrame <= 0)
		{
			system("CLS"); //this is terrabad... don't use it
			clearConsolePerFrame = 10;
		}
		
		printLine("deltaTime: " + std::to_string(deltaTime));
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