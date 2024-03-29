#ifndef OBJECTALLOCATOR__H_
#define OBJECTALLOCATOR__H_

class Object;

#include "Object.h"
#include <vector>

class ObjectAllocator
{
public:
	friend class Object;
	static ObjectAllocator* const Instance();

	void addToDestroyQueue(Object* obj);
	void processDestroyQueue();

private:
	ObjectAllocator();
	~ObjectAllocator();

	unsigned long ID_COUNTER;
	unsigned long GetID();
	void storeInstance(Object* inst);
	std::vector<Object*> instanceList;
	std::vector<Object*> destroyQueue;
	static ObjectAllocator* _instance;
};

#endif