#include "RenderComponent.h"

#include "RenderQueue.h"
#include "HelperFunctions.h"
#include "Camera.h"
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

void RenderComponent::initialise()
{
	//add reference to the renderqueue for this component
	enabled = true;
	RenderQueue::Instance()->AddToQueue(this);
	material = new Material();
}

bool RenderComponent::isActive()
{
	return enabled & owner->IsActive();
}

RenderComponent::RenderComponent()
{
}

RenderComponent::~RenderComponent()
{
	delete material;
	material = nullptr;
	printf("RenderComponent destructor called\n");
	RenderQueue::Instance()->removeFromQueue(id);
}
