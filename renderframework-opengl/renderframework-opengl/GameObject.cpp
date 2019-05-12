#include "GameObject.h"
#include "Timer.h"
#include "ObjectAllocator.h"

std::vector<GameObject*> GameObject::activeObjects;
std::vector<GameObject*> GameObject::inactiveObjects;
std::vector<unsigned int> GameObject::enableObjectQueue;
std::vector<unsigned int> GameObject::disableObjectQueue;

GameObject::GameObject(GameObject& org)
{
	printf("GameObject copy constructor called.\n");
	this->_instance = org._instance;
	org.copies.push_back(this);
	this->copies.push_back(&org);
	this->id = org.id;
	this->name = org.name;
}

GameObject & GameObject::Instantiate()
{
	activeObjects.push_back(&Object::Instantiate<GameObject>());
	//activeObjects[activeObjects.size() - 1]->_instance = activeObjects[activeObjects.size() - 1];
	//activeObjects[activeObjects.size() - 1]->initialiseUniqueInstance();
	return activeObjects[activeObjects.size()-1][0];
}

void GameObject::Destroy(GameObject& go)
{
	if (go._instance != nullptr)
	{
		ObjectAllocator::Instance()->addToDestroyQueue(go._instance);
		for (int i = 0; i < go->components.size(); ++i)
		{
			ObjectAllocator::Instance()->addToDestroyQueue(go->components[i]);
		}
		//remove it from the activity lists?
		go._instance = nullptr;
		go.clearReferences(&go);
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

std::string GameObject::toString()
{
	return name;
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

void GameObject::printReferenceInfo()
{
	if (copies.empty())
	{
		printf("%s has not been copied.\n", _instance->toString().c_str());
	}
	else
	{
		printf("[%s]GameObject container(ID:%i) has %i copies.\n", _instance->name.c_str(), id, copies.size());
		for (int i = 0; i < copies.size(); ++i)
		{
			printf("Copy(#%i): (%s) {Container ID: %i}\n", i + 1, copies[i]->_instance->toString().c_str(), id);
		}
	}
}

GameObject::GameObject()
{
	name = "dummy-empty-instance";
}

void GameObject::initialise()
{
	_instance = this;
	_instance->name = "go_" + std::to_string(id);
	_instance->components.reserve(2);
	_instance->enabled = true;
	printf("Gameobject[%s] init'd\n", _instance->name.c_str());
}

void GameObject::clearReferences(GameObject * original)
{
	if (original->copies.empty())
	{
		original->_instance = nullptr;
		return;
	}
	else
	{
		while (!original->copies.empty())
		{
			GameObject* cp = original->copies[original->copies.size() - 1];
			original->copies.pop_back();
			//cp->_instance = nullptr;
			clearReferences(cp);
		}
	}
}

void GameObject::operator delete(void * ptr)
{
	::delete (GameObject*)ptr; //call global delete
}

GameObject::~GameObject()
{
	//cleanup components?
	printf("\nGameobject destroyed\n");
	const char* outputtext = _instance == nullptr ? "reference copy(x)" : _instance->name.c_str();
	printf("[%s]GameObject being deleted.\n", outputtext);
	if (_instance != nullptr && copies.size() > 1)
		Destroy(*this);
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

GameObject & GameObject::operator *()
{
	return *_instance;
}

GameObject * GameObject::operator->()
{
	return _instance;
}

void GameObject::operator=(GameObject & org)
{
	printf("GameObject assignment operator called\n");
	this->_instance = org._instance;
	org.copies.push_back(this);
	this->copies.push_back(&org);
	this->id = org.id;
	this->name = org.name;
}

bool GameObject::operator==(const GameObject * ptr)
{
	if (ptr == nullptr)
		return _instance == (void*)ptr;
	return _instance == ptr->_instance;
}

bool GameObject::operator==(const GameObject & ptr)
{
	return _instance == ptr._instance;
}

bool GameObject::operator!=(const GameObject * ptr)
{
	if (ptr == nullptr)
		return _instance != (void*)ptr;
	return _instance != ptr->_instance;
}

bool GameObject::operator!=(const GameObject & ptr)
{
	return _instance != ptr._instance;
}
