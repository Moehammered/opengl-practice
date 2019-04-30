#ifndef GAMEOBJECT__H_
#define GAMEOBJECT__H_

class Component; //resolve cyclical dependency (forward decleration)

#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "StaticMesh.h"
#include <vector>


class GameObject : public Object
{
public:

	friend class Scene;
	friend class Object;
	static GameObject* const Instantiate();
	static void Destroy(GameObject*& go);
	static void ProcessPostUpdate();
	std::string name;
	std::vector<Component*> components;
	Transform transform;

	template <class C>
	C* const AddComponent();
	void SetActive(bool state);
	bool IsActive();

protected:
	GameObject();
	~GameObject();

	bool enabled;

	static std::vector<GameObject*> activeObjects;
	static std::vector<GameObject*> inactiveObjects;
	static std::vector<unsigned int> enableObjectQueue;
	static std::vector<unsigned int> disableObjectQueue;
	static void addToEnableQueue(unsigned int ID);
	static void addToDisableQueue(unsigned int ID);
	static void processActiveState();
};


template<class C>
inline C* const GameObject::AddComponent()
{
	assert((std::is_base_of<Component, C>::value));
	C* comp = new C();
	Component* casted = (Component*)comp;
	casted->owner = this;
	components.push_back(comp);
	return comp;
}



#endif

