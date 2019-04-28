#ifndef OBJECT__H_
#define OBJECT__H_

class ObjectAllocator;

#include "ObjectAllocator.h"

class Object
{
public:
	friend class ObjectAllocator;
	virtual void initialise();
	virtual void cleanup();

	template <class O>
	O* const Instantiate();

protected:
	unsigned long id;
	Object();
	virtual ~Object();
};

template<class O>
inline O * const Object::Instantiate()
{
	assert((std::is_base_of<Object, O>::value));
	O* obj = new O();
	Object* casted = (Object*)obj;
	casted->id = ObjectAllocator::Instance()->GetID();
	obj->initialise();
	ObjectAllocator::Instance()->storeInstance(casted);

	return obj;
}



#endif