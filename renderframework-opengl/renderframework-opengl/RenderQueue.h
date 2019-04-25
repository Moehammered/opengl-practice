#ifndef RENDERQUEUE__H_
#define RENDERQUEUE__H_

#include <vector>
#include "RenderComponent.h"

class RenderQueue
{
public:
	friend class RenderComponent;
	static RenderQueue* const Instance();

	void processRenderQueue();

private:
	RenderQueue();
	~RenderQueue();

	void AddToQueue(RenderComponent* rendComp);
	void removeFromQueue(RenderComponent* rendComp);
	void removeFromQueue(unsigned int id);
	std::vector<RenderComponent*> renderers;

	static RenderQueue* _instance;
};

#endif