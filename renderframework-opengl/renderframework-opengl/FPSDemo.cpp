#include "FPSDemo.h"
#include "PrimitiveShapes.h"
#include <glad\glad.h>
#include "Input.h"
#include <GLFW\glfw3.h>
#include "Timer.h"

#include "FPSMovementComponent.h"
#include "RenderComponent.h"
#include "UIRenderComponent.h"
#include "TransformVisualiser.h"
#include "VolumeVisualiser.h"
#include "MeshRendererComponent.h"

//fps demo variables
bool lineMode;
glm::vec3 pl_rot;
float pl_movespeed;
float pl_rotationspeed;
float mouseSensitivity;
glm::vec3 pl_dir;
MeshRendererComponent* playerRenderer;
MeshRendererComponent* plMeshRend;
MeshRendererComponent* groundRenderer;
MeshRendererComponent* bigBoxRenderer;
UIRenderComponent* uiText;
TransformVisualiser* visualiser;
VolumeVisualiser* collisionRenderer;

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
	lineMode = false;

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
	comp->enablePitchRotation = false;

	/*playerRenderer = player->AddComponent<RenderComponent>();
	PrimitiveShapes::CreateCube(playerRenderer->mesh);
	playerRenderer->initialise();
	playerRenderer->material->setTexture(new Texture("awesomeface.png"));
	playerRenderer->enabled = false;*/

	VertexAttributes textureMatAttribs[] = {
		{
			0, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::pos))
		},
		{
			1, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::colour))
		},
		{
			2, 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::uv))
		}
	};

	plMeshRend = player->AddComponent<MeshRendererComponent>();
	plMeshRend->initialise();
	plMeshRend->material->setShader(new Shader("VertexColourTransform.vs", "VertexColourTransform.fs"));
	plMeshRend->material->setTexture(new Texture("awesomeface.png"));
	plMeshRend->enabled = true;

	groundRenderer = ground->AddComponent<MeshRendererComponent>();
	//PrimitiveShapes::CreateXZPlane(groundRenderer->mesh);
	groundRenderer->initialise();
	groundRenderer->material->setTexture(new Texture("brick.jpg"));
	groundRenderer->material->setAttributes(textureMatAttribs, 3);
	groundRenderer->setMesh(PrimitiveShapes::CreateXZPlane());

	bigBoxRenderer = bigBox->AddComponent<MeshRendererComponent>();
	//PrimitiveShapes::CreateCube(bigBoxRenderer->mesh);
	bigBoxRenderer->initialise();
	bigBoxRenderer->material->setTexture(new Texture("container.jpg"));
	bigBoxRenderer->material->setAttributes(textureMatAttribs, 3);
	bigBoxRenderer->setMesh(PrimitiveShapes::CreateCube());

	uiText = player->AddComponent<UIRenderComponent>();
	uiText->initialise();
	uiText->text = "TExt component lele";
	uiText->pos.y = 60;
	uiText->scale = 0.25f;

	visualiser = player->AddComponent<TransformVisualiser>();
	visualiser->initialise();

	BoxVolume collider(glm::vec3(0), 1);
	BoxVolume box2(glm::vec3(0.5f, 0, 0), 2);
	collisionRenderer = player->AddComponent<VolumeVisualiser>();
	collisionRenderer->volumeToRender = collider;
	collisionRenderer->initialise();
	collisionRenderer->lineWidth = 6;
}

void FPSDemo::update()
{
	Scene::update();

	if (Input::IsKeyHeld(GLFW_KEY_DOWN))
	{
		mainCam.transform.position -= mainCam.transform.Forward() * Timer::DeltaTime() * pl_movespeed;
		mainCam.updateView();
	}
	else if (Input::IsKeyHeld(GLFW_KEY_UP))
	{
		mainCam.transform.position += mainCam.transform.Forward() * Timer::DeltaTime() * pl_movespeed;
		mainCam.updateView();
	}

	if (Input::IsKeyPressed(GLFW_KEY_L))
	{
		if (lineMode)
		{
			lineMode = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			lineMode = true;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	
	if (Input::IsKeyPressed(GLFW_KEY_2))
	{
		if(playerRenderer)
		playerRenderer->enabled = !playerRenderer->enabled;
	}
	else if (Input::IsKeyPressed(GLFW_KEY_3))
	{
		if(player != nullptr)
		player->SetActive(!player->IsActive());
	}
	else if (Input::IsKeyPressed(GLFW_KEY_C)) //test key for object copies
	{
		GameObject playerCopy = player;
		if(player != nullptr)
			player.printReferenceInfo();
	}
	else if (Input::IsKeyPressed(GLFW_KEY_0))
	{
		GameObject::Destroy(player);
		//player = nullptr;
	}
	else if (Input::IsKeyPressed(GLFW_KEY_4))
	{
		if(bigBox != nullptr)
		bigBox->SetActive(!bigBox->IsActive());
	}
	else if (Input::IsKeyPressed(GLFW_KEY_5))
	{
		if(bigBoxRenderer)
		bigBoxRenderer->enabled = !bigBoxRenderer->enabled;
	}
	else if (Input::IsKeyPressed(GLFW_KEY_9))
	{
		GameObject::Destroy(bigBox);
	}

	if (player != nullptr)
	{
		uiText->text = player->transform.toString();
	}
}
