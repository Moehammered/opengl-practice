#ifndef COMPONENTUPDATEQUEUE__H_
#define COMPONENTUPDATEQUEUE__H_

#include <vector>
#include "UpdateableComponent.h"

class ComponentUpdateQueue
{
public:
	friend class UpdateableComponent;
	static ComponentUpdateQueue* const Instance();

	void updateComponents();

private:
	ComponentUpdateQueue();
	~ComponentUpdateQueue();

	void AddToQueue(UpdateableComponent* comp);
	std::vector<UpdateableComponent*> components;

	static ComponentUpdateQueue* _instance;
};

#endif