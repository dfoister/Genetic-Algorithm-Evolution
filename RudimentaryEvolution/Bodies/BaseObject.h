#ifndef BASEOBJECT_H_GUARD
#define BASEOBJECT_H_GUARD

#include "../Physics/RigidBody.h"
class EvolutionSimulation;
class RigidBody;
class CollisionBounds;

class BaseObject : public RigidBody
{
public:
	BaseObject();
	~BaseObject();

	void setCollider(CollisionBounds* c) {
		collider = c;
	}

	CollisionBounds* getCollider() const {
		return collider;
	}

	void updateCollider() {
		this->collider->setPosition(this->pos);
	}

	virtual bool updateObject(float dt) = 0;



protected:

	CollisionBounds* collider;
};

#endif

