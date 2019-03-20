#include "TransformHelperFunctions.h"
#include <glm\gtc\matrix_transform.hpp>

glm::mat4 transformToMatrix(Transform const &tr)
{
	glm::mat4 world(1);
	world = glm::translate(world, tr.position);
	glm::mat4 rotMat = glm::mat4_cast(tr.Rotation());
	world = world * rotMat; // right to left (rotate first, then move according to the world)
	world = glm::scale(world, tr.scale);

	return world;
}

glm::mat4 transformRotationToMatrix(Transform const &tr)
{
	return glm::mat4_cast(tr.Rotation());
}
