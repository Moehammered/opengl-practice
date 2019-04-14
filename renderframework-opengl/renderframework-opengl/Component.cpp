#include "Component.h"

#include <limits>

Component::Component()
{
	owner = INT_MAX;
	enabled = true;
}

Component::~Component()
{}

void Component::initialise()
{
}

void Component::update(float deltaTime)
{
}

bool Component::isAttached()
{
	return owner != INT_MAX;
}
