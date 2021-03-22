#include "BaseObject.h"

BaseObject::BaseObject()
{
	collider_ = nullptr;
}

BaseObject::~BaseObject()
{
	delete(collider_);
}
