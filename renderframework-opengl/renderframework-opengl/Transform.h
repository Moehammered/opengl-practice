#ifndef TRANSFORM__H_
#define TRANSFORM__H_

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <string>

class Transform
{
public:
	glm::vec3 position, scale;

	Transform();
	~Transform();

	//getters - protect the values that rely on each other when changed
	const glm::quat Rotation() const;
	glm::vec3 Up();
	glm::vec3 Forward();
	glm::vec3 Right();

	//setters
	void Rotation(glm::quat value);
	void translate(float x, float y, float z);
	void translate(glm::vec3 delta);
	void rotate(glm::vec3 axis, float angle);
	void lookAt(glm::vec3 target);

	std::string toString();

private:
	glm::vec3 up, forward, right;
	glm::quat rotation;
};

#endif