#include <vector>

class BaseObject;
class SimPhysics;

class EvolutionSimulation
{
public:
	EvolutionSimulation();
	~EvolutionSimulation();
		
	void update(float dt);
	void addNewObject(BaseObject* object);

protected:
	void InitialiseGame();
	void CreateWallColliders();

	SimPhysics* physics;
	float gameTime;

	std::vector<BaseObject*> gameObjects;
	std::vector<BaseObject*> newObjects;
};

