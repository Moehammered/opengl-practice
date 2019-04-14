#include "FPSDemo.h"
#include "PrimitiveShapes.h"
#include <glad\glad.h>
#include <glm\gtc\type_ptr.hpp>
#include "Input.h"
#include <GLFW\glfw3.h>
#include "Timer.h"

void checkInput(Transform& pl_tr)
{
	if (Input::IsKeyHeld(GLFW_KEY_W))
	{
		pl_tr.position += pl_tr.Forward() * 3.0f * Timer::DeltaTime();
	}
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
