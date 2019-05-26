#include "BoundingVolume.h"
#include "TransformHelperFunctions.h"

BoxVolume::BoxVolume()
{
	centre = glm::vec3(0);
	halfSize = glm::vec3(1);
	resizeVolume(centre, halfSize);
}

BoxVolume::BoxVolume(glm::vec3 centre, float size)
{
	resizeVolume(centre, glm::vec3(size/2.0f, size/2.0f, size/2.0f));
}

BoxVolume::BoxVolume(glm::vec3 size)
{
	resizeVolume(size - (size/2.0f), size/2.0f);
}

BoxVolume::BoxVolume(glm::vec3 minPoint, glm::vec3 maxPoint)
{
	glm::vec3 size = maxPoint - minPoint;
	resizeVolume(minPoint + size/2.0f, size/2.0f);
}

bool BoxVolume::intersect(glm::vec3 point)
{
	if (point.x > maxPoint.x)
		return false;
	else if (point.x < minPoint.x)
		return false;
	else //it's within the x axis
	{
		if (point.y > maxPoint.y)
			return false;
		else if (point.y < minPoint.y)
			return false;
		else //it's within the y axis
		{
			if (point.z > maxPoint.z)
				return false;
			else if (point.z < minPoint.z)
				return false;
		}
	}

	//if it gets here the point must've been within the bounds
	return true;
}

bool BoxVolume::intersect(BoxVolume & other)
{
	return false;
}

void BoxVolume::resizeVolume(glm::vec3 centre, glm::vec3 halfSize)
{
	this->centre = centre;
	this->halfSize = halfSize;
	minPoint = centre - halfSize;
	maxPoint = centre + halfSize;
}

std::string BoxVolume::toString()
{
	std::string output = "";
	output += "centre: " + vec3ToString(centre);
	output += "\nmin: " + vec3ToString(minPoint);
	output += "\nmax: " + vec3ToString(maxPoint);
	output += "\nhalfSize: " + vec3ToString(halfSize);
	return output;
}
