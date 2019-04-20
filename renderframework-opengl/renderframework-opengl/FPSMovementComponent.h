#ifndef FPSMOVEMENTCOMPONENT__H_
#define FPSMOVEMENTCOMPONENT__H_

#include "Component.h"
#include <glm\glm.hpp>

class FPSMovementComponent :
	public Component
{
public:
	FPSMovementComponent();
	~FPSMovementComponent();

	float movementSpeed;
	float rotationSpeed;
	float mouseSensitivity;

	void initialise();
	void update(float deltaTime);

private:

	glm::vec3 movementDirection, rotationAxis;

	void checkPlayerMovement(Transform& tr, float deltaTime);
	void checkPlayerRotation(Transform& tr, float deltaTime);
};

#endif