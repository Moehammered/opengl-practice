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
#include "RenderQueue.h"
#include "ComponentUpdateQueue.h"
#include "ObjectAllocator.h"

int main(char** argv, int argc)
{
	stbi_set_flip_vertically_on_load(true);
	OpenGLLoader* instance;
	ObjectAllocator* allocator;

	instance = OpenGLLoader::Instance();
	instance->setWindowSize(800, 600);

	if (!instance->initialiseOpenGL())
	{
		//error occurred...
		glfwTerminate();
		printLine("Window creation failed.");
		return -1;
	}

	Input::Initialise();
	glfwSetKeyCallback(instance->getWindow(), Input::StoreKeyState);

	//startup the timer
	Timer::tick();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	allocator = ObjectAllocator::Instance();
	RenderQueue* const gameRenderer = RenderQueue::Instance();
	ComponentUpdateQueue* const componentUpdater = ComponentUpdateQueue::Instance();
	FPSDemo fpsDemo;
	fpsDemo.initialise();
	glfwSetInputMode(instance->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	
	while (!glfwWindowShouldClose(instance->getWindow()))
	{
		//calculate timing and event variables
		Timer::tick();
		glfwPollEvents();
		Input::RecordMouseMovement();

		if (Input::IsKeyReleased(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(instance->getWindow(), true);
		}
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//tick entities
		fpsDemo.update();
		componentUpdater->updateComponents();

		//render
		gameRenderer->processRenderQueue();
		gameRenderer->processUIRenderQueue();
		
		//check for events and swap render buffers
		glfwSwapBuffers(instance->getWindow());
		Input::RecordKeys();

		//perform post update activities and tasks (toggling active state, managing pools and services, etc)
		GameObject::ProcessPostUpdate();
		allocator->processDestroyQueue();
	}

	glfwTerminate();

	return 0;
}
