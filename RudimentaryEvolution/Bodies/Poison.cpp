#include "Poison.h"

Poison::Poison()
{
	std::random_device rd;
	engine_.seed(rd());
	std::uniform_real_distribution<> distrX(10.0f, 1270.0f);
	std::uniform_real_distribution<> distrY(10.0f, 710.0f);

	float randomX = static_cast <float> (distrX(engine_));
	float randomY = static_cast <float> (distrY(engine_));

	pos_ = Eigen::Vector2f(randomX, randomY);

	collider_ = new Collider(Collider::Shapes::CIRCLE, Collider::Types::POISON, 4.0f);
	collider_->setColour(sf::Color::Red);
	collider_->setObject(this);
	updateCollider();

}

Poison::~Poison()
{
}

bool Poison::updateObject(float dt)
{

	if (isConsumed_) {
		return false;
	}

	updateCollider();
	return true;
}

