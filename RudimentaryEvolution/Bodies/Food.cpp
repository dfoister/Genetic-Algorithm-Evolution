#include "Food.h"
#include <random>

Food::Food()
{
	std::random_device rd;
	engine_.seed(rd());
	std::uniform_real_distribution<> distrX(10.0f, 1270.0f);
	std::uniform_real_distribution<> distrY(10.0f, 710.0f);

	float randomX = static_cast <float> (distrX(engine_));
	float randomY = static_cast <float> (distrY(engine_));

	pos_ = Eigen::Vector2f(randomX, randomY);

	collider_ = new Collider(Collider::Shapes::CIRCLE, Collider::Types::FOOD, 4.0f);
	collider_->setColour(sf::Color::Green);
	collider_->setObject(this);
	updateCollider();
}

Food::~Food()
{
}

bool Food::updateObject(float dt)
{
	updateCollider();

	if (isConsumed_) {
		return false;
	}
	return true;
}
