#ifndef COMPONENT__H_
#define COMPONENT__H_

class Component
{
public:
	Component();
	~Component();
	
	int owner;
	bool enabled;

	virtual void initialise();
	virtual void update(float deltaTime);

	bool isAttached();

protected:

};

#endif