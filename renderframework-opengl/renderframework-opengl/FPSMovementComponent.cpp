#include "FPSMovementComponent.h"

#include "Input.h"
#include "Timer.h"
#include <glm\gtx\norm.hpp>
#include <GLFW\glfw3.h>
#include "HelperFunctions.h"
#include "ComponentUpdateQueue.h"

FPSMovementComponent::FPSMovementComponent()
{
	movementSpeed = rotationSpeed = mouseSensitivity = 1;
	enablePitchRotation = false;
	//printLine("FPSMOVECOMP");
}

FPSMovementComponent::~FPSMovementComponent()
{
	printLine("Destroy FPSMOVECOMP");
	printf("Removing from queue....\n");
	ComponentUpdateQueue::Instance()->removeFromQueue(id);
}

void FPSMovementComponent::initialise()
{

}

void FPSMovementComponent::update()
{
	checkPlayerMovement(owner->transform, Timer::DeltaTime());
	checkPlayerRotation(owner->transform, Timer::DeltaTime());
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
	if (enablePitchRotation)
	{
		rotationAxis = glm::vec3(0);
		rotationAxis.x = Input::RawMouseMovementDelta().y;
		if (Input::IsKeyHeld(GLFW_KEY_UP))
			rotationAxis.x = 1;
		else if (Input::IsKeyHeld(GLFW_KEY_DOWN))
			rotationAxis.x = -1;

		if (glm::length2(rotationAxis) > 0.1f)
		{
			rotationAxis = glm::normalize(rotationAxis);
			tr.rotate(rotationAxis, rotationSpeed * deltaTime);
		}
	}
}
