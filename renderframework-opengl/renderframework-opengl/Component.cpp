#include "Component.h"

#include <limits>

unsigned long Component::ID_COUNTER = ULONG_MAX;

Component::Component()
{
	id = --ID_COUNTER;
	owner = nullptr;
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
	return owner != nullptr;
}
