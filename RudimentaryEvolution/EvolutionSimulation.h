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

	SimPhysics* physics_;
	Rendering* renderer_;
	float gameTime_;

	std::vector<BaseObject*> gameObjects_;
	std::vector<BaseObject*> newObjects_;
};

