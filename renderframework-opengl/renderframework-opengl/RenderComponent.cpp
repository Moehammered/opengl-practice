#include "RenderComponent.h"

#include "RenderQueue.h"
#include "HelperFunctions.h"
#include "Camera.h"
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

void RenderComponent::initialise()
{
	material = new Material();
}

bool RenderComponent::isActive()
{
	return enabled & owner->IsActive();
}

void RenderComponent::draw()
{
	if (material)
	{
		if (Camera::MainCamera)
		{
			material->use();
			material->setTransformProperty("transform", 
				Camera::MainCamera->ProjView() * owner->transform.TransformMat4());
			mesh.draw();
		}
	}
}

RenderComponent::RenderComponent()
{
	//add reference to the renderqueue for this component
	enabled = true;
	RenderQueue::Instance()->AddToQueue(this);
}

RenderComponent::~RenderComponent()
{
	delete material;
	printf("RenderComponent destructor called\n");
	RenderQueue::Instance()->removeFromQueue(id);
}
