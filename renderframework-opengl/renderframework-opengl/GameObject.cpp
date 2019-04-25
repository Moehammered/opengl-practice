#include "GameObject.h"
#include "Timer.h"

unsigned int GameObject::ID_COUNTER = 0;

std::vector<GameObject*> GameObject::activeObjects;
std::vector<GameObject*> GameObject::inactiveObjects;
std::vector<GameObject*> GameObject::destroyObjectQueue;
std::vector<unsigned int> GameObject::enableObjectQueue;
std::vector<unsigned int> GameObject::disableObjectQueue;
std::vector<Component*> GameObject::destroyComponentQueue;

GameObject* const GameObject::Instantiate()
{
	GameObject* go = new GameObject();
	activeObjects.push_back(go);

	return go;
}

void GameObject::Destroy(GameObject * go)
{
	addToDestroyQueue(go);
	destroyComponents(go);
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
	processDestroyRequests();
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
	id = ++ID_COUNTER;
	name = "go_" + std::to_string(id);
	components.reserve(2);
	enabled = true;
}

GameObject::~GameObject()
{
	//cleanup components?
}

void GameObject::addToDestroyQueue(GameObject * go)
{
	destroyObjectQueue.push_back(go);
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

void GameObject::processDestroyRequests()
{
	for (int i = 0; i < destroyObjectQueue.size(); ++i)
	{
		GameObject* currGO = destroyObjectQueue[i];
		if (currGO->IsActive())
		{
			for (int k = 0; k < activeObjects.size(); ++k)
			{
				if (activeObjects[k]->id == currGO->id)
				{
					activeObjects.erase(activeObjects.begin() + k);
					delete currGO;
					currGO = nullptr;
					break;
				}
			}
		}
		else
		{
			for (int k = 0; k < inactiveObjects.size(); ++k)
			{
				if (inactiveObjects[k]->id == currGO->id)
				{
					inactiveObjects.erase(inactiveObjects.begin() + k);
					delete currGO;
					currGO = nullptr;
					break;
				}
			}
		}
	}

	destroyObjectQueue.clear();

	for (int i = 0; i < destroyComponentQueue.size(); ++i)
	{
		delete destroyComponentQueue[i];
	}

	destroyComponentQueue.clear();
}

void GameObject::destroyComponents(GameObject * go)
{
	for (int i = 0; i < go->components.size(); ++i)
		destroyComponentQueue.push_back(go->components[i]);

	go->components.clear();
}
