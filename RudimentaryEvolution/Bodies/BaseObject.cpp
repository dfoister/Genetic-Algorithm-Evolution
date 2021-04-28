#include "BaseObject.h"

BaseObject::BaseObject()
{
	collider_ = nullptr;
	lifetime_ = 0.0f;
}

BaseObject::~BaseObject()
{
	delete(collider_);
}
