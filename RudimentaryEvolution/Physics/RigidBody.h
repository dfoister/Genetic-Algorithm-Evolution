#ifndef RIGIDBODY_H_GUARD
#define RIGIDBODY_H_GUARD

#include "CollisionPair.h"

using namespace Eigen;

class RigidBody
{
	friend class SimPhysics;
public:
	RigidBody();
	~RigidBody();

	void setPos(const Vector2f& newPos) {
		pos_ = newPos;
	}

	void setVel(const Vector2f& newVel) {
		velocity_ = newVel;
	}

	void setSpring(RigidBody* body) {
		this->spring_ = body;
	}

	void addForce(const Vector2f& newForce) {
		force_ += newForce;
	}

	void addImpulse(const Vector2f& newImpulse) {
		velocity_ += newImpulse * inverseMass_;
	}

	Vector2f getPos() const {
		return pos_;
	}

	Vector2f getVel() const {
		return velocity_;
	}

	float getHealth() {
		return currentHealth_;
	}

	void updateSprings() {
		const float c = 1;
		const float snappiness = 1;
		Vector2f delta = this->getPos() - spring_->getPos();

		Vector2f normal = BasicVector2Operations::normalized(delta);

		float force = -snappiness * (BasicVector2Operations::length(delta) - 10);
		float relativeVelocity = (spring_->getVel() - this->getVel()).dot(normal);
		float forceDampened = force - c * relativeVelocity;
		this->addForce(normal * forceDampened);
	}

	void consumedFoodPoison(std::string type) {

			if (type == "FOOD") {
				currentHealth_ += 25;
			}
			else {
				currentHealth_ -= 40;
			}

	}

protected:
	Vector2f pos_;
	Vector2f velocity_;
	Vector2f force_;
	float damp_;
	float inverseMass_;
	float elasticity_;
	RigidBody* spring_;

	float currentHealth_;
	bool isConsumed_; 
};

#endif
