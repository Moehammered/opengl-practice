#include "ObjectAllocator.h"

ObjectAllocator* ObjectAllocator::_instance = nullptr;

ObjectAllocator * const ObjectAllocator::Instance()
{
	if (_instance)
		return _instance;

	_instance = new ObjectAllocator();
	return _instance;
}

void ObjectAllocator::addToDestroyQueue(Object * obj)
{
	destroyQueue.push_back(obj);
}

void ObjectAllocator::processDestroyQueue()
{
	for (int i = 0; i < destroyQueue.size(); ++i)
	{
		if (destroyQueue[i] != nullptr)
		{
			for (int k = 0; k < instanceList.size(); ++k)
			{
				if (instanceList[k]->id == destroyQueue[i]->id)
				{
					instanceList.erase(instanceList.begin() + k);
					delete destroyQueue[i];
					destroyQueue[i] = nullptr;
					break;
				}
			}
		}
	}

	destroyQueue.clear();
}

ObjectAllocator::ObjectAllocator()
{
	ID_COUNTER = 0;
	instanceList.reserve(30);
}

ObjectAllocator::~ObjectAllocator()
{
	for (int i = 0; i < instanceList.size(); ++i)
	{
		delete instanceList[i];
	}

	instanceList.clear();
}

unsigned long ObjectAllocator::GetID()
{
	return ID_COUNTER++;
}

void ObjectAllocator::storeInstance(Object * inst)
{
	instanceList.push_back(inst);
}
