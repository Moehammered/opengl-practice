#include "FPSDemo.h"
#include "PrimitiveShapes.h"
#include <glad\glad.h>
#include "Input.h"
#include <GLFW\glfw3.h>
#include "Timer.h"

#include "FPSMovementComponent.h"
#include "RenderComponent.h"

//fps demo variables
glm::vec3 pl_rot;
float pl_movespeed;
float pl_rotationspeed;
float mouseSensitivity;
glm::vec3 pl_dir;
RenderComponent* playerRenderer;
RenderComponent* groundRenderer;

void setupCamera(Camera& cam)
{
	cam.transform.position = glm::vec3(3, 18, 15);
	cam.transform.lookAt(glm::vec3(0));
	cam.updateView();
}

FPSDemo::FPSDemo()
{
}


FPSDemo::~FPSDemo()
{
}

void FPSDemo::cleanup()
{
	delete transformShader;
	delete containerTexture;

	transformShader = nullptr;
	containerTexture = nullptr;
}

void FPSDemo::initialise()
{
	setupCamera(mainCam);

	xAxis = Line(glm::vec3(0, 0, 0), glm::vec3(50, 0, 0), Colour::Red());
	yAxis = Line(glm::vec3(0, 0, 0), glm::vec3(0, 50, 0), Colour::Green());
	zAxis = Line(glm::vec3(0, 0, 0), glm::vec3(0, 0, -50), Colour::Blue());

	player = GameObject::Instantiate();
	player->transform.position = glm::vec3(0,2,0);
	player->transform.scale = glm::vec3(3, 3, 3);

	ground = GameObject::Instantiate();
	ground->name = "ground";
	ground->transform.position = glm::vec3(0);
	ground->transform.scale = glm::vec3(10, 1, 10);

	transformShader = new Shader("transform-coltex-shader.vs", "coltex-shader.fs");
	containerTexture = new Texture("container.jpg");

	pl_movespeed = 10;
	pl_rotationspeed = 180;
	mouseSensitivity = 2;

	FPSMovementComponent* comp = player->AddComponent<FPSMovementComponent>();
	comp->movementSpeed = pl_movespeed;
	comp->rotationSpeed = pl_rotationspeed;
	comp->mouseSensitivity = mouseSensitivity;

	playerRenderer = player->AddComponent<RenderComponent>();
	playerRenderer->shaderMaterial = transformShader;
	playerRenderer->shaderTexture = containerTexture;
	PrimitiveShapes::CreateCube(playerRenderer->mesh);
	playerRenderer->initialise();

	groundRenderer = ground->AddComponent<RenderComponent>();
	//printLine("Ground owner: " + groundRenderer->owner->name);
	groundRenderer->shaderMaterial = transformShader;
	groundRenderer->shaderTexture = containerTexture;
	PrimitiveShapes::CreateXZPlane(groundRenderer->mesh);
	groundRenderer->initialise();
}

void FPSDemo::update()
{
	Scene::update();

	if (Input::IsKeyPressed(GLFW_KEY_1))
	{
		playerRenderer->enabled = true;
	}
	else if (Input::IsKeyPressed(GLFW_KEY_2))
	{
		playerRenderer->enabled = false;
	}
}
