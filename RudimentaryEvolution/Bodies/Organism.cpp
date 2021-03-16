#include "Organism.h"

Organism::Organism()
{
	collider = new CollisionBounds(CollisionBounds::Shapes::CIRCLE, CollisionBounds::Types::ORGANISM, 14.0f);
	//collider = new CollisionVolume(CollisionVolume::Shapes::BOX, CollisionVolume::Types::PLAYER, 25.0f,25.0f);
	inverseMass = 0.3f;
}

Organism::~Organism()
{
}

bool Organism::updateObject(float dt)
{
	return true;
}
