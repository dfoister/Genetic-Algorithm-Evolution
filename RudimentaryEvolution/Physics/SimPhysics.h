#include <vector>

#include "RigidBody.h"

using namespace Eigen;

class RigidBody;
class CollisionBounds;
class CollisionPair;
class SimPhysics
{
public: 
	SimPhysics();
	~SimPhysics();

	void addBody(RigidBody* b);
	void removeBody(RigidBody* b);

	void addCollider(CollisionBounds* c);
	void removeCollider(CollisionBounds* c);

	void update(float dt);


protected:

	void integration(float dt);
	void collisionDetection(float dt);
	void collisionResolution(float dt);
	void integrateVel(float dt);

	std::vector<RigidBody*> allBodies;
	std::vector<CollisionBounds*> allColliders;
	std::vector<CollisionPair*> collisionList;
};

