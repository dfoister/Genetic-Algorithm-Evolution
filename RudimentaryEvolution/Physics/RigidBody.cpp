#include "RigidBody.h"

RigidBody::RigidBody() {
	inverseMass = 1.0f;
	elasticity = 0.5f;
	damp = 0.99f;
	spring = nullptr;
}


RigidBody::~RigidBody() {

}
