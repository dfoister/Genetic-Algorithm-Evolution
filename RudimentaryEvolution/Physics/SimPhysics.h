#include <vector>
#include "RigidBody.h"

using namespace Eigen;

class RigidBody;
class Collider;
class CollisionPair;
class SimPhysics
{
public: 
	SimPhysics();
	~SimPhysics();

	void addBody(RigidBody* b);
	void removeBody(RigidBody* b);

	void addCollider(Collider* c);
	void removeCollider(Collider* c);

	void update(float dt);


protected:

	void integration(float dt);
	void collisionDetection(float dt);
	void collisionResolution(float dt);
	void integrateVel(float dt);

	std::vector<RigidBody*> allBodies_;
	std::vector<Collider*> allColliders_;
	std::vector<CollisionPair*> collisionList_;
};

