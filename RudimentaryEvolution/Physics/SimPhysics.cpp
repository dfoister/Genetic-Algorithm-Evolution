#include "SimPhysics.h"
#include <tuple>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace Eigen;

SimPhysics::SimPhysics()
{
}

SimPhysics::~SimPhysics()
{
}

void SimPhysics::addBody(RigidBody* b) {
	allBodies_.emplace_back(b);
}

void SimPhysics::removeBody(RigidBody* b) {
	auto at = std::find(allBodies_.begin(), allBodies_.end(), b);

	if (at != allBodies_.end()) {
		//maybe delete too?
		allBodies_.erase(at);
	}
}

void SimPhysics::addCollider(Collider* c) {
	allColliders_.emplace_back(c);
}

void SimPhysics::removeCollider(Collider* c) {
	auto at = std::find(allColliders_.begin(), allColliders_.end(), c);

	if (at != allColliders_.end()) {
		//maybe delete too?
		allColliders_.erase(at);
	}
}

void SimPhysics::update(float dt) {
	
	integration(dt);
	collisionDetection(dt);
	collisionResolution(dt);
	integrateVel(dt);


	// Reset all forces back to 0.
	for (RigidBody* body : allBodies_) {
		body->force_ = Vector2f(0, 0);
	}
}

void SimPhysics::integration(float dt) {
	
	for (RigidBody* body : allBodies_) {
		Vector2f acceleration = body->force_ * body->inverseMass_;
		body->vel_ += acceleration * dt;
		body->vel_ *= body->damp_;
	}

}

void SimPhysics::integrateVel(float dt)
{
	for (RigidBody* body : allBodies_) {
		body->pos_ += body->vel_ * dt;
	}
}

void SimPhysics::collisionDetection(float dt) {

	for (size_t i = 0; i < allColliders_.size(); i++) {
		for (size_t j = i + 1; j < allColliders_.size(); j++) {

			bool result;
			float penetration;
			Vector2f normal;


			if (allColliders_[i]->getType() != Collider::Types::WALL || allColliders_[j]->getType() != Collider::Types::WALL) {

				// isCollided returns true/false, penetration amount and normal vector.
				std::tie(result, penetration, normal) = allColliders_[i]->isCollided(allColliders_[j]);

				if (result == true) {  // If collided


					CollisionPair* temp = new CollisionPair(allColliders_[i], allColliders_[j], penetration, normal);

					// Adds the collision pair to a list
					collisionList_.push_back(temp);

				}
			}
		}
	}

	// Outputs every collision occuring each frame.
	for (CollisionPair* c : collisionList_) {
		//std::cout << "COLLISION: " << c->getCollisionA()->getName() << " + " << c->getCollisionB()->getName() << "  Penetration: " << c->getPenetration() << "  Normal: " << c->getNormal();
	}
}

/*
void SimPhysics::SortAndSweep() {

	std::sort(allColliders.begin(), allColliders.end(), [](const CollisionBounds* lhs, const CollisionBounds* rhs)
		{
			return lhs->minExtentX < rhs->minExtentX;
		});


	for (int i = 0; i < allColliders.size(); i++) {
		potentialCollisions.emplace_back(allColliders[i]);

		for (int j = 0; i < potentialCollisions.size(); j++) {

			if (allColliders[i]->getMaxExtentX() > allColliders[j]->getMinExtentX()) {

				if (CheckPossibleIntersection(allColliders[i], allColliders[j])) {
					evenMorePotentialCollisions.emplace_back(allColliders[i]);
					evenMorePotentialCollisions.emplace_back(allColliders[j]);
				}

			}
			else {
				potentialCollisions.erase(potentialCollisions.begin() + j);
			}
		}
	}
}

bool NCL::CSC3222::SimPhysics::CheckPossibleIntersection(CollisionBounds* lhs, CollisionBounds* rhs) {
	float ignore;
	Vector2f ignore2;
	bool collided;

	if (lhs->getShape() == CollisionBounds::Shapes::BOX && rhs->getShape() == CollisionBounds::Shapes::BOX) {

		lhs->isCollided(rhs) = std::make_tuple(collided, ignore, ignore2);
		return collided;
	}
	else {

		CollisionBounds* lhsNew = new CollisionBounds(CollisionBounds::Shapes::BOX, CollisionBounds::Types::UNKNOWN, lhs->getWidth(), lhs->getHeight());
		CollisionBounds* rhsNew = new CollisionBounds(CollisionBounds::Shapes::BOX, CollisionBounds::Types::UNKNOWN, rhs->getWidth(), rhs->getHeight());
		lhsNew->isCollided(rhsNew) = std::make_tuple(collided, ignore, ignore2);
		return collided;
	}
}
*/

void SimPhysics::collisionResolution(float dt)
{

	for (CollisionPair* pair : collisionList_) {


		if ((pair->getCollisionA()->getName() == "FOOD" || pair->getCollisionA()->getName() == "POISON") && pair->getCollisionB()->getName() == "ORGANISM") {
			pair->getCollisionB()->getObject()->consumedFoodPoison(pair->getCollisionA()->getName()); 
			pair->getCollisionA()->getObject()->isConsumed_ = 1;
		} 
		else if (pair->getCollisionA()->getName() == "ORGANISM" && (pair->getCollisionB()->getName() == "FOOD" || pair->getCollisionB()->getName() == "POISON")) {
			pair->getCollisionA()->getObject()->consumedFoodPoison(pair->getCollisionA()->getName());
			pair->getCollisionB()->getObject()->isConsumed_ = 1;
		}
		else {

		RigidBody* a = pair->getCollisionA()->getObject();
		RigidBody* b = pair->getCollisionB()->getObject();

		float massA = a->inverseMass_;
		float massB = b->inverseMass_;
		float totalMass = massA + massB;

		a->pos_ -= pair->getNormal() * pair->getPenetration() * (massA / totalMass);
		b->pos_ += pair->getNormal() * pair->getPenetration() * (massB / totalMass);


		Vector2f relativeVelocity = a->vel_ - b->vel_;
		float relativeVelDotCollisionNormal = relativeVelocity.dot(pair->getNormal());
		float coefficientOfRestitution = 0.8f;

		float j = (-(1 + coefficientOfRestitution) * relativeVelDotCollisionNormal) / totalMass;

		a->addImpulse(a->vel_ + massA * j * pair->getNormal());
		b->addImpulse(b->vel_ - massB * j * pair->getNormal());

		}

	}

	// Clears the collision pair list and potential collisions at the end of the frame.
	collisionList_.clear();
}


