#ifndef ORGANISM_H
#define ORGANISM_H
#include "BaseObject.h"
class Organism : public BaseObject {
public:
	Organism();
	Organism(std::vector<float> chromosome);
	~Organism();
	bool updateObject(float dt) override;

	std::vector<float> getChromosome();
	void setChromosome(std::vector<float> chromosome);
	
	std::vector<float> chromosome_;

	float getSpeed();
	float getTurningSpeed();
	float getBodySize();
	float getFoodRadius();
	float getPoisonRadius();
	float getBaseHealth();
	float getLifetime();

	void setNearestHealth(Vector2f pos);
	void setNearestPoison(Vector2f pos);
	void setNearPoison(bool y);
	void setNearHealth(bool y);


protected:
	float normalSpeed_;
	float foodPoisonImpulse_;
	float bodySize_;
	float foodRadius_;
	float poisonRadius_;
	float baseHealth_;

	Vector2f nearestHealth_;
	Vector2f nearestPoison_;
	bool nearHealth_;
	bool nearPoison_;
};
#endif

