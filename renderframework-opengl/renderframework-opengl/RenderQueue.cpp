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
		if (renderers[i]->enabled)
			renderers[i]->draw();
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
