#include <vector>
#include "Graphics/Rendering.h"

class BaseObject;
class SimPhysics;

class EvolutionSimulation
{
public:
	EvolutionSimulation(Rendering* r);
	~EvolutionSimulation();
		
	void update(float dt);
	void addNewObject(BaseObject* object);

protected:
	void InitialiseGame();
	void CreateWallColliders();

	SimPhysics* physics;
	Rendering* renderer;
	float gameTime;

	std::vector<BaseObject*> gameObjects;
	std::vector<BaseObject*> newObjects;
	Rendering* r;
};

