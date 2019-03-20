#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

Transform::Transform()
{
	position = glm::vec3(0);
	scale = glm::vec3(1);
	rotation = glm::quat();
	forward = glm::vec3(0, 0, -1);
	right = glm::vec3(1, 0, 0);
	up = glm::vec3(0, 1, 0);
}


Transform::~Transform()
{
}

const glm::quat Transform::Rotation() const
{
	return rotation;
}

glm::vec3 Transform::Up()
{
	return up;
}

glm::vec3 Transform::Forward()
{
	return forward;
}

glm::vec3 Transform::Right()
{
	return right;
}

void Transform::Rotation(glm::quat value)
{
	rotation = value;
	//recalculate up, forward, right
	up = glm::vec3(0, 1, 0) * rotation;
	forward = glm::vec3(0, 0, -1) * rotation;
	right = glm::vec3(1, 0, 0) * rotation;
}

void Transform::translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}

void Transform::translate(glm::vec3 delta)
{
	position += delta;
}

void Transform::rotate(glm::vec3 axis, float angle)
{
	Rotation(glm::angleAxis(glm::radians(angle), axis) * rotation);
}

void Transform::lookAt(glm::vec3 target)
{
	glm::vec3 newDirection = target - position;
	newDirection = glm::normalize(newDirection);
	//create new rotation using world forward, up and the new direction
	glm::mat4 rot = glm::lookAt(position, target, glm::vec3(0, 1, 0));
	Rotation(glm::quat_cast(rot));
	//Rotation(glm::Rotation)
}
