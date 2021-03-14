#include <vector>
#include <Eigen/geometry>
#include "RigidBody.h"

using namespace Eigen;

class SimPhysics
{
public: 
	SimPhysics();
	~SimPhysics();

	void AddBody(RigidBody* b);
	void RemoveBody(RigidBody* b);

	void AddCollider(CollisionBounds* c);
	void RemoveCollider(CollisionBounds* c);

	void Update(float dt);


protected:

	void Integration(float dt);
	void CollisionDetection(float dt);
	void CollisionResolution(float dt);
	void IntegrateVelocity(float dt);

	std::vector<RigidBody*> allBodies;
	std::vector<CollisionBounds*> allColliders;
	std::vector<CollisionPair*> collisionList;
};

