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
		if (components[i]->enabled)
			components[i]->update();
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
