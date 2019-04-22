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
}

void UpdateableComponent::update()
{
}
