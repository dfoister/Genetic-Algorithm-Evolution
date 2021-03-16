#include "Wall.h"


Wall::Wall()
{
	inverseMass = 0;
}

Wall::Wall(CollisionBounds* col, Vector2f position)
{
	collider = col;
	this->pos = position;
	updateCollider();
}

Wall::~Wall()
{
}

bool Wall::updateObject(float dt)
{
	return true;
}
