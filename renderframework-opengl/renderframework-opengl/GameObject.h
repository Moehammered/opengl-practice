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
	static void ProcessPostUpdate();
	unsigned int id;
	std::string name;
	std::vector<Component*> components;
	Transform transform;

	template <class C>
	C* const AddComponent();
	void SetActive(bool state);
	bool IsActive();

private:
	GameObject();
	~GameObject();

	bool enabled;

	static unsigned int ID_COUNTER;
	static std::vector<GameObject*> activeObjects;
	static std::vector<GameObject*> inactiveObjects;
	static std::vector<GameObject*> destroyObjectQueue;
	static std::vector<Component*> destroyComponentQueue;
	static std::vector<unsigned int> enableObjectQueue;
	static std::vector<unsigned int> disableObjectQueue;

	static void addToDestroyQueue(GameObject* go);
	static void addToEnableQueue(unsigned int ID);
	static void addToDisableQueue(unsigned int ID);
	static void processActiveState();
	static void processDestroyRequests();
	static void destroyComponents(GameObject* go);
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

