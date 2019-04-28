#include "ObjectAllocator.h"

ObjectAllocator* ObjectAllocator::_instance = nullptr;

ObjectAllocator * const ObjectAllocator::Instance()
{
	if (_instance)
		return _instance;

	_instance = new ObjectAllocator();
	return _instance;
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
