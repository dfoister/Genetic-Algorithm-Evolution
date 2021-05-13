#ifndef EVOLUTIONSIMULATION_H
#define EVOLUTIONSIMULATION_H

#include <vector>
#include "Graphics/Rendering.h"

class BaseObject;
class SimPhysics;
class Organism;

class EvolutionSimulation
{
public:
	EvolutionSimulation(Rendering* r);
	~EvolutionSimulation();
		
	void update(float dt);
	void addNewObject(BaseObject* object);
	void InitialiseSim();
protected:

	void CreateWallColliders();

	SimPhysics* physics_;
	Rendering* renderer_;
	float simTime_;
	int generation_;

	std::vector<BaseObject*> simObjects_;
	std::vector<BaseObject*> newObjects_;
	std::vector<Organism*> oldOrganisms_;
};

#endif

