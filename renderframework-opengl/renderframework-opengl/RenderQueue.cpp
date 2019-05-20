#include "RenderQueue.h"

RenderQueue* RenderQueue::_instance = nullptr;

RenderQueue * const RenderQueue::Instance()
{
	if (_instance)
		return _instance;
	
	_instance = new RenderQueue();

	return _instance;
}

void RenderQueue::processRenderQueue()
{
	for (int i = 0; i < renderers.size(); ++i)
	{
		if (renderers[i]->isActive())
			renderers[i]->draw();
	}
}

void RenderQueue::processUIRenderQueue()
{
	for (int i = 0; i < uiRenderers.size(); ++i)
	{
		if (uiRenderers[i]->isActive())
			uiRenderers[i]->draw();
	}
}

RenderQueue::RenderQueue()
{
	renderers.reserve(10);
}


RenderQueue::~RenderQueue()
{
	delete _instance;
	_instance = nullptr;
}

void RenderQueue::AddToQueue(RenderComponent * rendComp)
{
	renderers.push_back(rendComp);
}

void RenderQueue::AddToQueue(UIRenderComponent * rendComp)
{
	uiRenderers.push_back(rendComp);
}

void RenderQueue::removeFromQueue(RenderComponent * rendComp)
{
	for (int i = 0; i < renderers.size(); ++i)
	{
		if (renderers[i]->id == rendComp->id)
		{
			renderers.erase(renderers.begin() + i);
			break;
		}
	}
}

void RenderQueue::removeFromQueue(unsigned int id)
{
	for (int i = 0; i < renderers.size(); ++i)
	{
		if (renderers[i]->id == id)
		{
			renderers.erase(renderers.begin() + i);
			break;
		}
	}
}

void RenderQueue::removeFromQueue(UIRenderComponent * rendComp)
{
	for (int i = 0; i < uiRenderers.size(); ++i)
	{
		if (uiRenderers[i]->id == rendComp->id)
		{
			uiRenderers.erase(uiRenderers.begin() + i);
			break;
		}
	}
}
