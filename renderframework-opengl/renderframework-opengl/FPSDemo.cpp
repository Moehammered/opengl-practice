#include "FPSDemo.h"
#include "PrimitiveShapes.h"
#include <glad\glad.h>
#include <glm\gtc\type_ptr.hpp>
#include "Input.h"
#include <GLFW\glfw3.h>
#include "Timer.h"

//fps demo variables
glm::vec3 pl_rot;
float pl_movespeed;
float pl_rotationspeed;
glm::vec3 pl_dir;

void checkPlayerMovement(Transform& pl_tr)
{
	pl_dir = glm::vec3(0);

	if (Input::IsKeyHeld(GLFW_KEY_W))
		pl_dir += pl_tr.Forward();
	else if (Input::IsKeyHeld(GLFW_KEY_S))
		pl_dir -= pl_tr.Forward();
	if (Input::IsKeyHeld(GLFW_KEY_A))
		pl_dir -= pl_tr.Right();
	else if (Input::IsKeyHeld(GLFW_KEY_D))
		pl_dir += pl_tr.Right();

	if (glm::length(pl_dir) > 0.4f)
	{
		pl_dir = glm::normalize(pl_dir);
		pl_tr.position += pl_dir * pl_movespeed * Timer::DeltaTime();
	}
}

void checkPlayerRotation(Transform& pl_tr)
{
	pl_rot = glm::vec3(0);

	/*if (Input::IsKeyHeld(GLFW_KEY_RIGHT))
		pl_rot.y = -1;
	else if (Input::IsKeyHeld(GLFW_KEY_LEFT))
		pl_rot.y = 1;*/

	pl_rot.y = -Input::MouseMovementDelta().x * Timer::DeltaTime();

	if (glm::length(pl_rot) > 0.5f)
	{
		pl_tr.rotate(glm::normalize(pl_rot), pl_rotationspeed * Timer::DeltaTime());
	}
}

void checkInput(Transform& pl_tr)
{
	checkPlayerMovement(pl_tr);
	checkPlayerRotation(pl_tr);
}

void setupCamera(Camera& cam)
{
	cam.transform.position = glm::vec3(3, 18, 15);
	cam.transform.lookAt(glm::vec3(0));
	cam.updateView();
}

void setupMeshes(StaticMesh& playerMesh, StaticMesh& ground)
{
	PrimitiveShapes::CreateCube(playerMesh);
	PrimitiveShapes::CreateXZPlane(ground);
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
	setupMeshes(playerMesh, ground);
	xAxis = Line(glm::vec3(0, 0, 0), glm::vec3(50, 0, 0), Colour::Red());
	yAxis = Line(glm::vec3(0, 0, 0), glm::vec3(0, 50, 0), Colour::Green());
	zAxis = Line(glm::vec3(0, 0, 0), glm::vec3(0, 0, -50), Colour::Blue());

	player.transform.position = glm::vec3(0,2,0);
	player.transform.scale = glm::vec3(3, 3, 3);

	groundTransform.position = glm::vec3(0);
	groundTransform.scale = glm::vec3(10, 1, 10);

	transformShader = new Shader("transform-coltex-shader.vs", "coltex-shader.fs");
	containerTexture = new Texture("container.jpg");

	pl_movespeed = 10;
	pl_rotationspeed = 180;
}

void FPSDemo::update(float deltaTime)
{
	checkInput(player.transform);

	unsigned int transformLoc = glGetUniformLocation(transformShader->ID(), "transform");
	
	transformShader->use();
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, 
		glm::value_ptr(mainCam.ProjView() * groundTransform.TransformMat4()));
	containerTexture->use();
	ground.draw();

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
		glm::value_ptr(mainCam.ProjView() * player.transform.TransformMat4()));
	playerMesh.draw();
}
