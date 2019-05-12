#include "Object.h"

void Object::initialise()
{
	printf("\nI'm initialising myself\n");
}

void Object::cleanup()
{
	printf("\nI'm cleaning myself up!\n");
}

Object::Object()
{
	id = 0;
}

Object::~Object()
{
	cleanup();
}
