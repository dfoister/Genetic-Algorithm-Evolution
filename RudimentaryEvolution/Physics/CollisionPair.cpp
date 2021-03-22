#include "CollisionPair.h"


CollisionPair::CollisionPair()
{
	a_ = NULL;
	b_ = NULL;
	normal_ = Vector2f(0, 0);
	penetration_ = 0;
}

CollisionPair::CollisionPair(Collider* a, Collider* b, float penetration, Vector2f normal)
{
	this->a_ = a;
	this->b_ = b;
	this->normal_ = normal;
	this->penetration_ = penetration;
}

CollisionPair::~CollisionPair()
{
}

Collider* CollisionPair::getCollisionA() const
{
	return a_;
}



Collider* CollisionPair::getCollisionB() const
{
	return b_;
}

float CollisionPair::getPenetration()
{
	return penetration_;
}

Vector2f CollisionPair::getNormal()
{
	return normal_;
}
