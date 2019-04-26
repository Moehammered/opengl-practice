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
RenderComponent* bigBoxRenderer;

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
	GameObject::Destroy(player);
	GameObject::Destroy(ground);
	GameObject::Destroy(bigBox);
}

void FPSDemo::cleanup()
{
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

	bigBox = GameObject::Instantiate();
	bigBox->name = "prop box";
	bigBox->transform.position = glm::vec3(4, 2, -4);
	bigBox->transform.rotate(glm::vec3(0, 1, 0), 45);
	bigBox->transform.scale = glm::vec3(4,4,4);

	pl_movespeed = 10;
	pl_rotationspeed = 180;
	mouseSensitivity = 2;

	FPSMovementComponent* comp = player->AddComponent<FPSMovementComponent>();
	comp->movementSpeed = pl_movespeed;
	comp->rotationSpeed = pl_rotationspeed;
	comp->mouseSensitivity = mouseSensitivity;

	playerRenderer = player->AddComponent<RenderComponent>();
	PrimitiveShapes::CreateCube(playerRenderer->mesh);
	playerRenderer->initialise();
	playerRenderer->material->setTexture(new Texture("awesomeface.png"));

	groundRenderer = ground->AddComponent<RenderComponent>();
	PrimitiveShapes::CreateXZPlane(groundRenderer->mesh);
	groundRenderer->initialise();
	groundRenderer->material->setTexture(new Texture("brick.jpg"));

	bigBoxRenderer = bigBox->AddComponent<RenderComponent>();
	PrimitiveShapes::CreateCube(bigBoxRenderer->mesh);
	bigBoxRenderer->initialise();
	bigBoxRenderer->material->setTexture(new Texture("container.jpg"));
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
	else if (Input::IsKeyPressed(GLFW_KEY_3))
	{
		player->SetActive(!player->IsActive());
	}
	else if (Input::IsKeyPressed(GLFW_KEY_0))
	{
		GameObject::Destroy(player);
	}
	else if (Input::IsKeyPressed(GLFW_KEY_4))
	{
		bigBox->SetActive(!bigBox->IsActive());
	}
	else if (Input::IsKeyPressed(GLFW_KEY_5))
	{
		bigBoxRenderer->enabled = !bigBoxRenderer->enabled;
	}
	else if (Input::IsKeyPressed(GLFW_KEY_9))
	{
		GameObject::Destroy(bigBox);
	}
}
