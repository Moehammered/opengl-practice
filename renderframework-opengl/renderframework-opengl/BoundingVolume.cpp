#include "BoundingVolume.h"
#include "TransformHelperFunctions.h"
#include <glm\gtx\norm.hpp>
#include <iostream>

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
	//early out method of checking squared distance from other
	/*float sqrDist = glm::length2(this->centre - other.centre - other.halfSize);
	float sqrSize = glm::length2(this->centre + this->halfSize);
	std::cout << "Sqr dist: " << sqrDist << "\nSqr size: " << sqrSize << std::endl;
	if (sqrDist > sqrSize)
		return false;*/
	
	//let's find the closest point to the centre from the other
	glm::vec3 pointToCheck;
	if (other.centre.x > this->centre.x) //the other box is to the right
		pointToCheck.x = other.minPoint.x;
	else
		pointToCheck.x = other.maxPoint.x;
	if (other.centre.y > this->centre.y) //the other box is above
		pointToCheck.y = other.minPoint.y;
	else
		pointToCheck.y = other.maxPoint.y;
	if (other.centre.z > this->centre.z) //the other box is behind
		pointToCheck.z = other.minPoint.z;
	else
		pointToCheck.z = other.maxPoint.z;

	std::cout << "Testing point: " << vec3ToString(pointToCheck) << std::endl;

	return intersect(pointToCheck);
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
