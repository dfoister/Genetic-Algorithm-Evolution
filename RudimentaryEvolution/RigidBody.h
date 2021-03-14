#include <Eigen/Dense>
#include "BasicVector2Operations.h"
#include "CollisionPair.h"

using namespace Eigen;

class RigidBody
{
	friend class SimPhysics;
public:
	RigidBody();
	~RigidBody();

	void setPos(const Vector2f& newPos) {
		pos = newPos;
	}

	void setVel(const Vector2f& newVel) {
		vel = newVel;
	}

	void setSpring(RigidBody* body) {
		this->spring = body;
	}

	void AddForce(const Vector2f& newForce) {
		force += newForce;
	}

	void AddImpulse(const Vector2f& newImpulse) {
		vel += newImpulse * inverseMass;
	}

	Vector2f GetPos() const {
		return pos;
	}

	Vector2f GetVel() const {
		return vel;
	}

	void updateSprings() {
		const float c = 1;
		const float snappiness = 1;
		Vector2f delta = this->GetPos() - spring->GetPos();

		Vector2f normal = BasicVector2Operations::normalized(delta);

		float force = -snappiness * (BasicVector2Operations::length(delta) - 10);
		float relativeVelocity = (spring->GetVel() - this->GetVel()).dot(normal);
		float forceDampened = force - c * relativeVelocity;
		this->AddForce(normal * forceDampened);
	}



protected:
	Vector2f pos;
	Vector2f vel;
	Vector2f force;
	float damp;
	float inverseMass;
	float elasticity;
	RigidBody* spring;

};

