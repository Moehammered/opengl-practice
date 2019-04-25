#include "ComponentUpdateQueue.h"

ComponentUpdateQueue* ComponentUpdateQueue::_instance = nullptr;

ComponentUpdateQueue * const ComponentUpdateQueue::Instance()
{
	if (_instance)
		return _instance;

	_instance = new ComponentUpdateQueue();
	return _instance;
}

void ComponentUpdateQueue::updateComponents()
{
	for (int i = 0; i < components.size(); ++i)
	{
		if (components[i])
		{
			if (components[i] != nullptr & components[i]->isActive())
				components[i]->update();
		}
	}
}

ComponentUpdateQueue::ComponentUpdateQueue()
{
	components.reserve(20);
}


ComponentUpdateQueue::~ComponentUpdateQueue()
{
	delete _instance;
	_instance = nullptr;
}

void ComponentUpdateQueue::AddToQueue(UpdateableComponent * comp)
{
	components.push_back(comp);
}

void ComponentUpdateQueue::removeFromQueue(UpdateableComponent * comp)
{
	for (int i = 0; i < components.size(); ++i)
	{
		if (components[i]->id == comp->id)
		{
			components.erase(components.begin() + i);
			break;
		}
	}
}

void ComponentUpdateQueue::removeFromQueue(unsigned int id)
{
	for (int i = 0; i < components.size(); ++i)
	{
		if (components[i]->id == id)
		{
			components.erase(components.begin() + i);
			break;
		}
	}
}
