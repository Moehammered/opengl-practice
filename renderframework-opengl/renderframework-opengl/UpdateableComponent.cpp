#include "UpdateableComponent.h"

#include "ComponentUpdateQueue.h"

UpdateableComponent::UpdateableComponent()
{
	//add itself to the update queue
	enabled = true;
	ComponentUpdateQueue::Instance()->AddToQueue(this);
}


UpdateableComponent::~UpdateableComponent()
{
	printf("Removing from queue....\n");
	ComponentUpdateQueue::Instance()->removeFromQueue(this);
}

void UpdateableComponent::update()
{
}

bool UpdateableComponent::isActive()
{
	return enabled & owner->IsActive();
}
