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
#include "BoundingVolume.h"
#include "TransformHelperFunctions.h"
#include "VertexArrayObject.h"
#include "PrimitiveShapes.h"

struct TestContainer {
	VertexArrayObject vao;
	Transform tr;
	//need to fix the initialisation order to allow stack allocation
	Material* mat;
	Mesh mesh;
};

void printCollisionTest(BoxVolume& vol1, BoxVolume& vol2)
{
	std::cout << "\nCollider[1] info\n" << vol1.toString() << std::endl;
	std::cout << "\nCollider[2] info\n" << vol2.toString() << std::endl;
	std::cout << "Does it intersect? " << vol1.intersect(vol2) << std::endl;
}

void printCollisionTest(BoxVolume& collider, glm::vec3 testPoint)
{
	std::cout << "\nCollider info\n" << collider.toString() << std::endl;
	std::cout << "\nTest intersection point: " << vec3ToString(testPoint) << std::endl;
	std::cout << "Does it intersect? " << collider.intersect(testPoint) << std::endl;
}

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

	BoxVolume collider(glm::vec3(0), 2);
	glm::vec3 testPoint = glm::vec3(0.5f, 0, 0);
	glm::vec3 p2 = glm::vec3(0);
	glm::vec3 p3 = glm::vec3(3, 0, -0.7f);
	glm::vec3 p4 = glm::vec3(-1, -0.3f, 0.667f);
	printCollisionTest(collider, testPoint);
	printCollisionTest(collider, p2);
	printCollisionTest(collider, p3);
	printCollisionTest(collider, p4);

	BoxVolume box2(glm::vec3(0.5f, 0, 0), 2);
	BoxVolume box3(glm::vec3(0,3,0), 0.5f);
	printCollisionTest(collider, box2);
	printCollisionTest(box3, box2);

	///setup block for a de-coupled mesh and vao
	TestContainer momentOfTruth;
	{
		PrimitiveShapes::CreateCube(momentOfTruth.mesh);
		//Mesh mesh = momentOfTruth.mesh;
		//int* indices = mesh.Indices();
		BufferProperty buffers[] = {
			{
				GL_ARRAY_BUFFER, sizeof(Vertex) * momentOfTruth.mesh.VertexCount(), momentOfTruth.mesh.Vertices(), GL_STATIC_DRAW
			},
			{
				GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * momentOfTruth.mesh.IndexCount(), momentOfTruth.mesh.Indices(), GL_STATIC_DRAW
			}
		};
		VertexAttributes attributes[] = {
			{
				0, 3, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::pos))
			},
			{
				1, 3, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::colour))
			}
		};
		momentOfTruth.vao.setupBuffers(buffers, 2);
		momentOfTruth.vao.setupAttributes(attributes, 2);
		momentOfTruth.mat = new Material("VertexColourTransform.vs", "VertexColourTransform.fs");
		momentOfTruth.tr.position = glm::vec3(0, 0, -3);
	}
	///setup block for a de-coupled mesh and vao

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
		glClearColor(0.08f, 0.08f, 0.09f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//tick entities
		fpsDemo.update();
		componentUpdater->updateComponents();

		//render
		gameRenderer->processRenderQueue();
		
		/*momentOfTruth.mat->use();
		momentOfTruth.vao.bindVAO();

			momentOfTruth.mat->setTransformProperty("transform",
				Camera::MainCamera->ProjView() * momentOfTruth.tr.TransformMat4());
			glDrawElements(momentOfTruth.mesh.MeshType(),
				momentOfTruth.mesh.IndexCount(), GL_UNSIGNED_INT, 0);

		momentOfTruth.vao.unbind();*/

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
