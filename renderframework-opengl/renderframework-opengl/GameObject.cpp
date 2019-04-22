#include "GameObject.h"
#include "Timer.h"

unsigned int GameObject::ID_COUNTER = 0;

std::vector<GameObject*> GameObject::activeObjects;

GameObject* const GameObject::Instantiate()
{
	GameObject* go = new GameObject();
	activeObjects.push_back(go);

	return go;
}

void GameObject::Destroy(GameObject * go)
{
	for (int i = 0; i < activeObjects.size(); ++i)
	{
		if (activeObjects[i]->id == go->id)
		{
			activeObjects.erase(activeObjects.begin() + i);
			delete go;
			go = nullptr;

			break;
		}
	}
}

GameObject::GameObject()
{
	id = ++ID_COUNTER;
	name = "go_" + std::to_string(id);
	components.reserve(2);
}

GameObject::~GameObject()
{
	//cleanup components?
}

//void GameObject::UpdateGameObjects()
//{
//	for (int i = 0; i < activeObjects.size(); ++i)
//	{
//		UpdateComponents(activeObjects[i]->components);
//	}
//}
//
//void GameObject::UpdateComponents(std::vector<Component*>& comps)
//{
//	for (int i = 0; i < comps.size(); ++i)
//	{
//		if (comps[i]->enabled)
//			comps[i]->update(Timer::DeltaTime());
//	}
//}
