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
	GameObject();
	~GameObject();

	unsigned int id;
	std::string name;
	std::vector<Component*> components;
	Transform transform;

	template <class C>
	C* const AddComponent();

private:
	static unsigned int ID_COUNTER;
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

