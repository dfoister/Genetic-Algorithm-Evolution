#ifndef BASEOBJECT_H_GUARD
#define BASEOBJECT_H_GUARD

#include "../Physics/RigidBody.h"
#include <random>
class EvolutionSimulation;
class RigidBody;
class Collider;

class BaseObject : public RigidBody
{
public:
	BaseObject();
	~BaseObject();

	void setCollider(Collider* c) {
		collider_ = c;
	}

	Collider* getCollider() const {
		return collider_;
	}

	void updateCollider() {
		this->collider_->setPosition(this->pos_);
	}

	virtual bool updateObject(float dt) = 0;

protected:

	Collider* collider_;
};

#endif

