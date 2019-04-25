#include "Component.h"

#include <limits>

unsigned long Component::ID_COUNTER = ULONG_MAX;

Component::Component()
{
	id = --ID_COUNTER;
	owner = nullptr;
}

Component::~Component()
{
	printf("Base component destructor called\n");
}

void Component::initialise()
{
}

bool Component::isAttached()
{
	return owner != nullptr;
}

bool Component::isActive()
{
	return owner->IsActive();
}
