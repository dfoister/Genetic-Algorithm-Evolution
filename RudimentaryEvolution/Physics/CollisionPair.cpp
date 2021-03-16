#include "CollisionPair.h"


CollisionPair::CollisionPair()
{
	a = NULL;
	b = NULL;
	normal = Vector2f(0, 0);
	penetration = 0;
}

CollisionPair::CollisionPair(CollisionBounds* a, CollisionBounds* b, float penetration, Vector2f normal)
{
	this->a = a;
	this->b = b;
	this->normal = normal;
	this->penetration = penetration;
}

CollisionPair::~CollisionPair()
{
}

CollisionBounds* CollisionPair::getCollisionA() const
{
	return a;
}



CollisionBounds* CollisionPair::getCollisionB() const
{
	return b;
}

float CollisionPair::getPenetration()
{
	return penetration;
}

Vector2f CollisionPair::getNormal()
{
	return normal;
}
