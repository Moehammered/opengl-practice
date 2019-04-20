#ifndef GAMEOBJECT__H_
#define GAMEOBJECT__H_

class Component; //resolve cyclical dependency (forward decleration)

#include "Component.h"
#include "Transform.h"
#include "StaticMesh.h"
#include <vector>


class GameObject
{
public:

	friend class Scene;
	static GameObject* const Instantiate();
	static void Destroy(GameObject* go);
	unsigned int id;
	std::string name;
	std::vector<Component*> components;
	Transform transform;

	template <class C>
	C* const AddComponent();

private:
	GameObject();
	~GameObject();

	static unsigned int ID_COUNTER;
	static std::vector<GameObject*> activeObjects;

	static void UpdateGameObjects();
	static void UpdateComponents(std::vector<Component*>& comps);
};


template<class C>
inline C* const GameObject::AddComponent()
{
	assert((std::is_base_of<Component, C>::value));
	C* comp = new C();
	Component* casted = (Component*)comp;
	casted->owner = this;
	casted->enabled = true;
	components.push_back(comp);
	return comp;
}

#endif

