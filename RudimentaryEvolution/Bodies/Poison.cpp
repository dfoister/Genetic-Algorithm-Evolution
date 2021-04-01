#include "Poison.h"

Poison::Poison()
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<> distrX(10, 1270);
	std::uniform_real_distribution<> distrY(10, 710);

	float randomX = static_cast <float> (distrX(eng));
	float randomY = static_cast <float> (distrY(eng));

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
