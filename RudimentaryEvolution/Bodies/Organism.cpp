#include "Organism.h"
#include "../Constants.h"
#include <iostream>

Organism::Organism()
{
	std::random_device rdPos;
	engine_.seed(rdPos());

	//std::default_random_engine eng(rd());
	std::uniform_real_distribution<> distrX(16.0f, 1264.0f);
	std::uniform_real_distribution<> distrY(16.0f, 704.0f);
	//eng.seed(time(0));
	float randomX = static_cast <float> (distrX(engine_));
	float randomY = static_cast <float> (distrY(engine_));

	pos_ = Eigen::Vector2f(randomX, randomY);


	collider_ = new Collider(Collider::Shapes::CIRCLE, Collider::Types::ORGANISM, 10.0f);
	collider_->setColour(sf::Color::Magenta);
	collider_->setObject(this);
	updateCollider();

	inverseMass_ = 0.3f;
	
	std::uniform_real_distribution<> distrBaseStats(90.0f, 110.0f);

	forwardSpeed_ = static_cast <float> (distrBaseStats(engine_));
	turningSpeed_ = static_cast <float> (distrBaseStats(engine_));
	bodySize_ = static_cast <float> (distrBaseStats(engine_));
	baseHealth_ = static_cast <float> (distrBaseStats(engine_));
	foodRadius_ = static_cast <float> (distrBaseStats(engine_));
	poisonRadius_ = static_cast <float> (distrBaseStats(engine_));
	
	std::cout << forwardSpeed_ << "," << turningSpeed_ << "," << bodySize_ << "," << baseHealth_ << "," << foodRadius_ << "," << poisonRadius_ << "\n";

	chromosome_.emplace_back(forwardSpeed_);
	chromosome_.emplace_back(turningSpeed_);
	chromosome_.emplace_back(bodySize_);
	chromosome_.emplace_back(baseHealth_);
	chromosome_.emplace_back(foodRadius_);
	chromosome_.emplace_back(poisonRadius_);

	currentHealth_ = baseHealth_;
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


	std::random_device rdMove;

	engine_.seed(rdMove());
	std::uniform_real_distribution<> distrX(-2.5f, 2.5f);
	std::uniform_real_distribution<> distrY(-2.5f, 2.5f);


	float randomX = static_cast <float> (distrX(engine_));
	float randomY = static_cast <float> (distrY(engine_));

	addForce((Eigen::Vector2f(randomX, randomY).normalized() * (forwardSpeed_*2.5f) ));

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

