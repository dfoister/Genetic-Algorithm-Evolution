#include "BaseObject.h"
class Organism : public BaseObject {
public:
	Organism();
	~Organism();
	bool updateObject(float dt) override;

	std::vector<float> getChromosome();
	void setChromosome(std::vector<float> chromosome);
	

protected:
	float forwardSpeed_;
	float turningSpeed_;
	float bodySize_;
	float foodRadius_;
	float poisonRadius_;
	float baseHealth_;
	std::vector<float> chromosome_;

	
};

