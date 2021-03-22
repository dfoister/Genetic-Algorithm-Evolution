#include "RigidBody.h"

RigidBody::RigidBody() {
	inverseMass_ = 0.3f;
	elasticity_ = 0.5f;
	damp_ = 0.99f;
	spring_ = nullptr;
	isConsumed_ = 0;
}


RigidBody::~RigidBody() {

}
