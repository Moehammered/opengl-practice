#ifndef COMPONENT__H_
#define COMPONENT__H_

class GameObject; //resolves cyclical dependency (forward decleration)
class Object;

#include "GameObject.h"


class Component : public Object
{
public:
	friend class GameObject;
	friend class Object;
	GameObject* owner;

	virtual void initialise();

	bool isAttached();
	virtual bool isActive();

private:
	static unsigned long ID_COUNTER;

protected:
	Component();
	virtual ~Component();

};

#endif