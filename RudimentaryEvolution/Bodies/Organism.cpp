#include "Organism.h"

Organism::Organism()
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<> distrX(16, 1264);
	std::uniform_real_distribution<> distrY(16, 704);

	float randomX = static_cast <float> (distrX(eng));
	float randomY = static_cast <float> (distrY(eng));

	pos_ = Eigen::Vector2f(randomX, randomY);


	collider_ = new Collider(Collider::Shapes::CIRCLE, Collider::Types::ORGANISM, 10.0f);
	collider_->setColour(sf::Color::Magenta);
	collider_->setObject(this);
	updateCollider();

	inverseMass_ = 0.3f;
	
	

	chromosome_.emplace_back(forwardSpeed_);
	chromosome_.emplace_back(turningSpeed_);
	chromosome_.emplace_back(bodySize_);
	chromosome_.emplace_back(baseHealth_);
	chromosome_.emplace_back(foodRadius_);
	chromosome_.emplace_back(poisonRadius_);

	currentHealth_ = 100.0f;
}

Organism::~Organism()
{
}

bool Organism::updateObject(float dt)
{
	currentHealth_ -= 0.25f;
	if (currentHealth_ <= 0) {
		return false;
	}
	updateCollider();


	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<> distrX(-1, 1);
	std::uniform_real_distribution<> distrY(-1, 1);


	float randomX = static_cast <float> (distrX(eng));
	float randomY = static_cast <float> (distrY(eng));

	addForce(Eigen::Vector2f(randomX, randomY) * 250);

	return true;
}

std::vector<float> Organism::getChromosome()
{
	return chromosome_;
}

void Organism::setChromosome(std::vector<float> chromosome)
{
	forwardSpeed_ = chromosome.at(0);
	turningSpeed_ = chromosome.at(1);
	bodySize_ = chromosome.at(2);
	baseHealth_ = chromosome.at(3);
	foodRadius_ = chromosome.at(4);
	poisonRadius_ = chromosome.at(5);
}

