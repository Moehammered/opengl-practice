#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <iostream>
#include "TransformHelperFunctions.h"

Transform::Transform()
{
	position = glm::vec3(0);
	scale = glm::vec3(1);
	Rotation(glm::quat());
	/*forward = glm::vec3(0, 0, -1);
	right = glm::vec3(1, 0, 0);
	up = glm::vec3(0, 1, 0);*/
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
	/*up = rotation * glm::vec3(0, 1, 0);
	forward = glm::vec3(0, 0, -1) * rotation;*/
	//right = glm::vec3(1, 0, 0) * rotation;
	//right = glm::cross(forward, up) * rotation;
	//up = glm::cross(forward, right);
	//working
	glm::mat4 rotMat = glm::mat4_cast(rotation);
	right = glm::vec3(rotMat[0][0], rotMat[0][1], rotMat[0][2]);
	up = glm::vec3(rotMat[1][0], rotMat[1][1], rotMat[1][2]);
	forward = -glm::normalize(glm::vec3(rotMat[2][0], rotMat[2][1], rotMat[2][2]));
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
	Rotation(rotation * glm::angleAxis(glm::radians(angle), axis));
}

//WORKS!!!! OMG THANK GOD!! --- https://stackoverflow.com/questions/18151845/converting-glmlookat-matrix-to-quaternion-and-back
void Transform::lookAt(glm::vec3 target)
{
	glm::vec3 newDirection = target - position;
	std::cout << "Look at (pre-normal): " << vec3ToString(newDirection) << std::endl;
	newDirection = glm::normalize(newDirection);
	std::cout << "Look at (post-normal): " << vec3ToString(newDirection) << std::endl;
	//create new rotation using world forward, up and the new direction
	glm::mat4 rot = glm::lookAt(position, target, up);
	Rotation(glm::conjugate(glm::toQuat(rot)));
	//Rotation(glm::Rotation)
}

std::string Transform::toString()
{
	std::string st;

	st.append("Position: (");
	st.append(std::to_string(position.x));
	st.append(", ");
	st.append(std::to_string(position.y));
	st.append(",");
	st.append(std::to_string(position.z));
	st.append(")");

	st.append("\nForward: (");
	st.append(std::to_string(forward.x));
	st.append(", ");
	st.append(std::to_string(forward.y));
	st.append(",");
	st.append(std::to_string(forward.z));
	st.append(")");

	st.append("\Right: (");
	st.append(std::to_string(right.x));
	st.append(", ");
	st.append(std::to_string(right.y));
	st.append(",");
	st.append(std::to_string(right.z));
	st.append(")");

	return st;
}
