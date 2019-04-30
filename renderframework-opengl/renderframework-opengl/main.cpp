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

void testClearPointer(int*& value)
{
	value = nullptr;
}

int main(char** argv, int argc)
{
	int* test = new int;
	test[0] = 5;

	printLine("test value: " + std::to_string(test[0]));
	printf("test addrs: 0x%p\n", (void*)test);
	testClearPointer(test);
	printf("test addrs: 0x%p\n", (void*)test);
	delete test;
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

	//printLine("MainCam?: " + std::to_string(Camera::MainCamera != nullptr));

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

		fpsDemo.update();

		componentUpdater->updateComponents();

		gameRenderer->processRenderQueue();
		
		//check for events and swap render buffers
		glfwSwapBuffers(instance->getWindow());
		Input::RecordKeys();

		GameObject::ProcessPostUpdate();
		allocator->processDestroyQueue();
	}

	glfwTerminate();

	return 0;
}