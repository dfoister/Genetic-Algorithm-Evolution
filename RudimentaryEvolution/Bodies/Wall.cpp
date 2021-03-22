#include "Wall.h"


Wall::Wall()
{
	inverseMass_ = 0;
}

Wall::Wall(Collider* col, Vector2f position)
{

	collider_ = col;
	collider_->setColour(sf::Color::Black);
	collider_->setObject(this);
	this->pos_ = position;
	updateCollider();
}

Wall::~Wall()
{
}

bool Wall::updateObject(float dt)
{
	return true;
}
