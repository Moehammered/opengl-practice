#pragma once

#include <glm\glm.hpp>
#include <string>

struct BoxVolume {
public:
	glm::vec3 centre;
	glm::vec3 halfSize;
	glm::vec3 minPoint, maxPoint;
	
	BoxVolume();
	BoxVolume(glm::vec3 centre, float size);
	BoxVolume(glm::vec3 size);
	BoxVolume(glm::vec3 minPoint, glm::vec3 maxPoint);

	bool intersect(glm::vec3 point);
	bool intersect(BoxVolume& other);

	void resizeVolume(glm::vec3 centre, glm::vec3 halfSize);
	std::string toString();
};