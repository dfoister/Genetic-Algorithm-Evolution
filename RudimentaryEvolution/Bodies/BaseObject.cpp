#include "BaseObject.h"

BaseObject::BaseObject()
{
	collider = nullptr;
}

BaseObject::~BaseObject()
{
	delete(collider);
}
