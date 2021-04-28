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
	void InitialiseGame();
protected:

	void CreateWallColliders();

	SimPhysics* physics_;
	Rendering* renderer_;
	float gameTime_;
	int generation_;

	std::vector<BaseObject*> gameObjects_;
	std::vector<BaseObject*> newObjects_;
	std::vector<Organism*> oldOrganisms_;
};

#endif

