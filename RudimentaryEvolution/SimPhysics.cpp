#include "SimPhysics.h"
#include <tuple>
#include <vector>
#include <algorithm>
#include <iterator>

void SimPhysics::AddBody(RigidBody* b) {
	allBodies.emplace_back(b);
}

void SimPhysics::RemoveBody(RigidBody* b) {
	auto at = std::find(allBodies.begin(), allBodies.end(), b);

	if (at != allBodies.end()) {
		//maybe delete too?
		allBodies.erase(at);
	}
}

void SimPhysics::AddCollider(CollisionBounds* c) {
	allColliders.emplace_back(c);
}

void SimPhysics::RemoveCollider(CollisionBounds* c) {
	auto at = std::find(allColliders.begin(), allColliders.end(), c);

	if (at != allColliders.end()) {
		//maybe delete too?
		allColliders.erase(at);
	}
}

void SimPhysics::Update(float dt) {
	Integration(dt);
	CollisionDetection(dt);
	CollisionResolution(dt);
	IntegrateVelocity(dt);


	// Reset all forces back to 0.
	for (auto body : allBodies) {
		body->force = Vector2f(0, 0);
	}
}

void SimPhysics::Integration(float dt) {
	for (auto body : allBodies) {
		Vector2f acceleration = body->force * body->inverseMass;
		body->vel += acceleration * dt;
		body->vel *= body->damp;
	}

}

void SimPhysics::IntegrateVelocity(float dt)
{
	for (auto body : allBodies) {
		body->pos += body->vel * dt;
	}
}

void SimPhysics::CollisionDetection(float dt) {

	for (int i = 0; i < allColliders.size(); i++) {
		for (int j = i + 1; j < allColliders.size(); j++) {

			bool result;
			float penetration;
			Vector2f normal;


			if (allColliders[i]->getType() != CollisionBounds::Types::MAP || allColliders[j]->getType() != CollisionBounds::Types::MAP) {

				// isCollided returns true/false, penetration amount and normal vector.
				std::tie(result, penetration, normal) = allColliders[i]->isCollided(allColliders[j]);

				if (result == true) {  // If collided


					CollisionPair* temp = new CollisionPair(allColliders[i], allColliders[j], penetration, normal);

					// Adds the collision pair to a list
					collisionList.push_back(temp);

				}
			}
		}
	}

	// Outputs every collision occuring each frame.
	for (CollisionPair* c : collisionList) {
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

void SimPhysics::CollisionResolution(float dt)
{
	// Clears the collision pair list and potential collisions at the end of the frame.
	collisionList.clear();
}


