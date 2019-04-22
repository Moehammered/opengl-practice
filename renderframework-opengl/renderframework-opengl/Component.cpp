#include "Component.h"

#include <limits>

unsigned long Component::ID_COUNTER = ULONG_MAX;

Component::Component()
{
	id = --ID_COUNTER;
	owner = nullptr;
}

Component::~Component()
{}

void Component::initialise()
{
}

bool Component::isAttached()
{
	return owner != nullptr;
}
