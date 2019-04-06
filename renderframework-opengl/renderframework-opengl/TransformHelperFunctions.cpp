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

std::string vec3ToString(glm::vec3 const & v3)
{
	std::string st;

	st.append("(");
	st.append(std::to_string(v3.x));
	st.append(", ");
	st.append(std::to_string(v3.y));
	st.append(",");
	st.append(std::to_string(v3.z));
	st.append(")");

	return st;
}
