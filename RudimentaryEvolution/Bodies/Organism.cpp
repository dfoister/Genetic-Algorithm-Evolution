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

	nearestHealth_, nearestPoison_ = pos_;
	nearHealth_, nearPoison_ = 0;


	collider_ = new Collider(Collider::Shapes::CIRCLE, Collider::Types::ORGANISM, 10.0f);
	collider_->setColour(sf::Color::Magenta);
	collider_->setObject(this);
	updateCollider();

	inverseMass_ = 0.3f;
	
	std::uniform_real_distribution<> distrBaseStats(80.0f, 120.0f);

	forwardSpeed_ = static_cast <float> (distrBaseStats(engine_));
	turningSpeed_ = static_cast <float> (distrBaseStats(engine_));
	bodySize_ = static_cast <float> (distrBaseStats(engine_));
	baseHealth_ = static_cast <float> (distrBaseStats(engine_));
	foodRadius_ = static_cast <float> (distrBaseStats(engine_));
	poisonRadius_ = static_cast <float> (distrBaseStats(engine_))/2;
	
	//std::cout << forwardSpeed_ << "," << turningSpeed_ << "," << bodySize_ << "," << baseHealth_ << "," << foodRadius_ << "," << poisonRadius_ << "\n";

	//std::cout << randomPop << "\n";

	chromosome_.emplace_back(forwardSpeed_);
	chromosome_.emplace_back(turningSpeed_);
	chromosome_.emplace_back(bodySize_);
	chromosome_.emplace_back(baseHealth_);
	chromosome_.emplace_back(foodRadius_);
	chromosome_.emplace_back(poisonRadius_);

	currentHealth_ = baseHealth_;
}

Organism::Organism(std::vector<float> chromosome):Organism()
{
	forwardSpeed_ = chromosome.at(0);
	turningSpeed_ = chromosome.at(1);
	bodySize_ = chromosome.at(2);
	baseHealth_ = chromosome.at(3);
	foodRadius_ = chromosome.at(4);
	poisonRadius_ = chromosome.at(5);
	currentHealth_ = baseHealth_;

	chromosome_.emplace_back(forwardSpeed_);
	chromosome_.emplace_back(turningSpeed_);
	chromosome_.emplace_back(bodySize_);
	chromosome_.emplace_back(baseHealth_);
	chromosome_.emplace_back(foodRadius_);
	chromosome_.emplace_back(poisonRadius_);
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

	if (!nearHealth_ && !nearPoison_) {

	std::random_device rdMove;

	engine_.seed(rdMove());
	std::uniform_real_distribution<> distrX(-2.5f, 2.5f);
	std::uniform_real_distribution<> distrY(-2.5f, 2.5f);


	float randomX = static_cast <float> (distrX(engine_));
	float randomY = static_cast <float> (distrY(engine_));

	addForce((Eigen::Vector2f(randomX, randomY).normalized() * (forwardSpeed_*2.5f) ));
	}
	if (nearHealth_) {

		Vector2f directionToFood = (nearestHealth_ - pos_).normalized();

		addForce(directionToFood * (turningSpeed_ * 3.0f));
		nearHealth_ = 0;
	}
	if (nearPoison_) {
		
		Vector2f directionToPoison = (nearestPoison_ - pos_).normalized();
		std::uniform_real_distribution<> distrChanceOfAvoidance(0.0f, 100.0f);
		float randomChance = static_cast <float> (distrChanceOfAvoidance(engine_));
		
		if (randomChance <= 25) addImpulse(-directionToPoison * (20.0f));
		nearPoison_ = 0;
	}

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
	currentHealth_ = baseHealth_;

	chromosome_.emplace_back(forwardSpeed_);
	chromosome_.emplace_back(turningSpeed_);
	chromosome_.emplace_back(bodySize_);
	chromosome_.emplace_back(baseHealth_);
	chromosome_.emplace_back(foodRadius_);
	chromosome_.emplace_back(poisonRadius_);
}

float Organism::getSpeed()
{
	return forwardSpeed_;
}

float Organism::getTurningSpeed()
{
	return turningSpeed_;
}

float Organism::getBodySize()
{
	return bodySize_;
}

float Organism::getFoodRadius()
{
	return foodRadius_;
}

float Organism::getPoisonRadius()
{
	return poisonRadius_;
}

float Organism::getBaseHealth()
{
	return baseHealth_;
}

void Organism::setNearestHealth(Vector2f pos)
{
	nearestHealth_ = pos;
}

void Organism::setNearestPoison(Vector2f pos)
{
	nearestPoison_ = pos;
}

void Organism::setNearPoison(bool y)
{
	nearPoison_ = y;
}

void Organism::setNearHealth(bool y)
{
	nearHealth_ = y;
}

