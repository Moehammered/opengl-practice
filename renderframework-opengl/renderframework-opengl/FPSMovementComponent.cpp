#include "FPSMovementComponent.h"

#include "Input.h"
#include <glm\gtx\norm.hpp>
#include <GLFW\glfw3.h>
#include "HelperFunctions.h"

FPSMovementComponent::FPSMovementComponent()
{
	movementSpeed = rotationSpeed = mouseSensitivity = 1;
	printLine("FPSMOVECOMP");
}

FPSMovementComponent::~FPSMovementComponent()
{
	printLine("Destroy FPSMOVECOMP");
}

void FPSMovementComponent::initialise()
{

}

void FPSMovementComponent::update(float deltaTime)
{
	checkPlayerMovement(owner->transform, deltaTime);
	checkPlayerRotation(owner->transform, deltaTime);
}

void FPSMovementComponent::checkPlayerMovement(Transform & tr, float deltaTime)
{
	movementDirection = glm::vec3(0);

	if (Input::IsKeyHeld(GLFW_KEY_W))
		movementDirection += tr.Forward();
	else if (Input::IsKeyHeld(GLFW_KEY_S))
		movementDirection -= tr.Forward();
	if (Input::IsKeyHeld(GLFW_KEY_A))
		movementDirection -= tr.Right();
	else if (Input::IsKeyHeld(GLFW_KEY_D))
		movementDirection += tr.Right();

	if (glm::length2(movementDirection) > 0.4f)
	{
		movementDirection = glm::normalize(movementDirection);
		tr.position += movementDirection * movementSpeed * deltaTime;
	}
}

void FPSMovementComponent::checkPlayerRotation(Transform & tr, float deltaTime)
{
	rotationAxis = glm::vec3(0);
	rotationAxis.y = -Input::RawMouseMovementDelta().x;

	if (glm::length2(rotationAxis) > 0.1f)
	{
		glm::vec3 finalAxis = glm::normalize(rotationAxis);
		tr.rotate(finalAxis, mouseSensitivity * rotationSpeed * deltaTime);
	}
}
