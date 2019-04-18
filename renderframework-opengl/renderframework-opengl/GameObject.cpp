#include "GameObject.h"

unsigned int GameObject::ID_COUNTER = 0;

GameObject::GameObject()
{
	id = ++ID_COUNTER;
	name = "go_" + std::to_string(id);
	components.reserve(2);
}

GameObject::~GameObject()
{
}
