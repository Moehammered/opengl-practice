#ifndef COMPONENT__H_
#define COMPONENT__H_

class GameObject; //resolves cyclical dependency (forward decleration)

#include "GameObject.h"


class Component
{
public:
	friend class GameObject;
	unsigned long id;
	GameObject* owner;

	virtual void initialise();

	bool isAttached();

private:
	static unsigned long ID_COUNTER;

protected:
	Component();
	~Component();

};

#endif