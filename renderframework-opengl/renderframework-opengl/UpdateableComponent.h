#ifndef UPDATEABLECOMPONENT__H_
#define UPDATEABLECOMPONENT__H_

#include "Component.h"
class UpdateableComponent :
	public Component
{
public:
	UpdateableComponent();
	~UpdateableComponent();

	bool enabled;

	virtual void update();
	bool isActive() override;
};

#endif