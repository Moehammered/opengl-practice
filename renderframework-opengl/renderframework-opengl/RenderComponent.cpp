#include "RenderComponent.h"

#include "RenderQueue.h"
#include "HelperFunctions.h"
#include "Camera.h"
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

void RenderComponent::initialise()
{
	if (shaderMaterial)
		shaderTransformLoc = glGetUniformLocation(shaderMaterial->ID(), "transform");
	//printLine("Shader Loc: " + std::to_string(shaderTransformLoc));
}

bool RenderComponent::isActive()
{
	return enabled & owner->IsActive();
}

void RenderComponent::draw()
{
	if (shaderMaterial)
	{
		if (Camera::MainCamera)
		{
			shaderMaterial->use();
			glUniformMatrix4fv(shaderTransformLoc, 1, GL_FALSE,
				glm::value_ptr(Camera::MainCamera->ProjView() * owner->transform.TransformMat4()));
			if (shaderTexture)
				shaderTexture->use();
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
	shaderMaterial = nullptr;
	shaderTexture = nullptr;
	printf("RenderComponent destructor called\n");
	RenderQueue::Instance()->removeFromQueue(id);
}
