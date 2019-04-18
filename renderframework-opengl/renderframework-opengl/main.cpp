#include <glad\glad.h>
#include <GLFW\glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "HelperFunctions.h"
#include "OpenGLLoader.h"
#include "Timer.h"
#include "FPSDemo.h"
#include "Input.h"
#include "TestComponent.h"

///globals
//screen
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

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
	Input::Initialise();
	glfwSetKeyCallback(instance->getWindow(), Input::StoreKeyState);


	//startup the timer
	Timer::tick();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	
	printLine("Is TestComponent derived from Component?");
	std::cout << std::is_base_of<Component, TestComponent>::value << '\n';

	GameObject testGO;
	testGO.AddComponent<TestComponent>();
	testGO.AddComponent<TestComponent>();
	printLine("GO Component count: " + std::to_string(testGO.components.size()));
	for (int i = 0; i < testGO.components.size(); ++i)
	{
		unsigned int compID = testGO.components[i]->id;
		printLine("comp[" + std::to_string(i) + "] id: " + std::to_string(compID));
	}
	printLine("GO Component count: " + std::to_string(testGO.components.size()));

	FPSDemo fpsDemo;
	fpsDemo.initialise();
	glfwSetInputMode(instance->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!glfwWindowShouldClose(instance->getWindow()))
	{
		//calculate timing variables
		Timer::tick();
		glfwPollEvents();
		Input::RecordMouseMovement();

		if (Input::IsKeyReleased(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(instance->getWindow(), true);
		}
		//render stuff
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		fpsDemo.update(Timer::DeltaTime());

		fpsDemo.updateGameObjects();
		
		//check for events and swap render buffers
		glfwSwapBuffers(instance->getWindow());
		Input::RecordKeys();
	}

	glfwTerminate();

	return 0;
}