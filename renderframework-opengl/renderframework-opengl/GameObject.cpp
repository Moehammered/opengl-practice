#include "GameObject.h"
#include "Timer.h"
#include "ObjectAllocator.h"

std::vector<GameObject*> GameObject::activeObjects;
std::vector<GameObject*> GameObject::inactiveObjects;
std::vector<unsigned int> GameObject::enableObjectQueue;
std::vector<unsigned int> GameObject::disableObjectQueue;

GameObject* const GameObject::Instantiate()
{
	GameObject* go = &Object::Instantiate<GameObject>();
	activeObjects.push_back(go);

	return go;
}

void GameObject::Destroy(GameObject*& go)
{
	if (go != nullptr)
	{
		ObjectAllocator::Instance()->addToDestroyQueue(go);
		for (int i = 0; i < go->components.size(); ++i)
		{
			ObjectAllocator::Instance()->addToDestroyQueue(go->components[i]);
		}
		//remove it from the activity lists?
		go = nullptr;
	}
	/*if (go)
	{
		addToDestroyQueue(go);
		destroyComponents(go);
		go = nullptr;
	}*/
	/*for (int i = 0; i < activeObjects.size(); ++i)
	{
		if (activeObjects[i]->id == go->id)
		{
			activeObjects.erase(activeObjects.begin() + i);
			delete go;
			go = nullptr;

			break;
		}
	}*/
}

void GameObject::ProcessPostUpdate()
{
	processActiveState();
}

void GameObject::SetActive(bool state)
{
	enabled = state;
	if (state)
		addToEnableQueue(id);
	else
		addToDisableQueue(id);
}

bool GameObject::IsActive()
{
	return enabled;
}

GameObject::GameObject()
{
	name = "go_" + std::to_string(id);
	components.reserve(2);
	enabled = true;
}

GameObject::~GameObject()
{
	//cleanup components?
	printf("\nGameobject destroyed");
}

void GameObject::addToEnableQueue(unsigned int ID)
{
	enableObjectQueue.push_back(ID);
}

void GameObject::addToDisableQueue(unsigned int ID)
{
	disableObjectQueue.push_back(ID);
}

void GameObject::processActiveState()
{
	//go through and enable
	for (int i = 0; i < enableObjectQueue.size(); ++i)
	{
		for (int k = 0; k < inactiveObjects.size(); ++k)
		{
			if (inactiveObjects[k]->id == enableObjectQueue[i])
			{
				activeObjects.push_back(inactiveObjects[k]);
				inactiveObjects.erase(inactiveObjects.begin() + k);
				k--;
			}
		}
	}

	//go through and disable now
	for (int i = 0; i < disableObjectQueue.size(); ++i)
	{
		for (int k = 0; k < activeObjects.size(); ++k)
		{
			if (activeObjects[k]->id == disableObjectQueue[i])
			{
				inactiveObjects.push_back(activeObjects[k]);
				activeObjects.erase(activeObjects.begin() + k);
				k--;
			}
		}
	}

	enableObjectQueue.clear();
	disableObjectQueue.clear();
}
