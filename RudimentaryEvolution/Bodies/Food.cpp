#include "Food.h"

Food::Food()
{
	collider = new CollisionBounds(CollisionBounds::Shapes::CIRCLE, CollisionBounds::Types::FOOD, 50.0f);
}

Food::~Food()
{
}

bool Food::updateObject(float dt)
{
	updateCollider();
	return true;
}
