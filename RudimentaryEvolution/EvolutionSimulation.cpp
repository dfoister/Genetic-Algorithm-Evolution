#include "EvolutionSimulation.h"
#include "Physics/SimPhysics.h"
#include "Bodies/BaseObject.h"
#include "Bodies/Food.h"
#include "Bodies/Wall.h"
#include "Bodies/Organism.h"
#include "Bodies/Poison.h"
#include "GeneticAlgorithm.h"
#include "Constants.h"
#include <iostream>

using namespace GLOBAL;

EvolutionSimulation::EvolutionSimulation(Rendering* r)
{
	physics_ = new SimPhysics();
	renderer_ = r;
	generation_ = -1;
	InitialiseSim();
	CreateWallColliders();
}

EvolutionSimulation::~EvolutionSimulation()
{
}



void EvolutionSimulation::addNewObject(BaseObject* object)
{
	newObjects_.emplace_back(object);
	physics_->addBody(object);
	if (object->getCollider()) {
		physics_->addCollider(object->getCollider());
	}
}

void EvolutionSimulation::update(float dt)
{
	renderer_->DrawText(sf::Vector2f(10, 10), "Generation: " + std::to_string(generation_));
	for (auto i : newObjects_) {
		simObjects_.emplace_back(i);
	}
	newObjects_.clear();

	simTime_ += dt;
	physics_->update(dt);


	for (auto i = simObjects_.begin(); i != simObjects_.end(); ) {
		if (!(*i)->updateObject(dt)) { //object has said its finished with
			
			if ((*i)->getCollider()->getName() == "FOOD") {
				addNewObject(new Food);
			}

			if ((*i)->getCollider()->getName() == "POISON") {
				addNewObject(new Poison);
			}

			if ((*i)->getCollider()->getName() == "ORGANISM") {
				Organism* o = dynamic_cast<Organism*>(*i);

				oldOrganisms_.emplace_back(o);
			}
			else {
				delete (*i);
			}
			physics_->removeCollider((*i)->getCollider());
			physics_->removeBody((*i));
			
			i = simObjects_.erase(i);
		}
		else {

			if ((*i)->getCollider()->colliderType_ == Collider::Types::ORGANISM) {

				Organism* o = dynamic_cast<Organism*>(*i);
				o->lifetime_ += dt;
				for (auto object : simObjects_) {
					if (object->getCollider()->colliderType_ == Collider::Types::FOOD) {

						Food* f = dynamic_cast<Food*>(object);


						if ((o->getPos() - f->getPos()).norm() < o->getFoodRadius()) {

							o->setNearHealth(1);
							o->setNearestHealth(f->getPos());
						}
					}

					if (object->getCollider()->colliderType_ == Collider::Types::POISON) {

						Poison* p = dynamic_cast<Poison*>(object);
						if ((o->getPos() - p->getPos()).norm() < (o->getPoisonRadius()/2)) {

							o->setNearestPoison(p->getPos());
							o->setNearPoison(1);

						}
					}


				}

			}

			Collider* col = (*i)->getCollider();
			if (col) {
				/// DRAWS ALL COLLIDER BOXES
				if (col->getName() == "FOOD" || col->getName() == "POISON") {
					renderer_->DrawCircle(sf::Vector2f(col->getPosition().x(), col->getPosition().y()), col->getRadius(), col->getColour());
				}
				else if(col->getName() == "ORGANISM"){
					renderer_->DrawOrganism(sf::Vector2f(col->getPosition().x(), col->getPosition().y()), col->getRadius(), col->getColour());
					//renderer_->DrawText(sf::Vector2f(col->getPosition().x(), col->getPosition().y()), std::to_string(col->getObject()->getHealth()));
				}
				else {
					renderer_->DrawBox(sf::Vector2f(col->getPosition().x(), col->getPosition().y()), col->getWidth(), col->getHeight(), col->getColour());
				}
				
			}
			

			++i;
		}
	}

	

}

void EvolutionSimulation::InitialiseSim()
{

	generation_ += 1;
	for (auto i = simObjects_.begin(); i != simObjects_.end(); ) {
		if ((*i)->getCollider()->getName() == "ORGANISM") {
			Organism* o = dynamic_cast<Organism*>(*i);
			oldOrganisms_.emplace_back(o);
		}
		else {
			delete (*i);
		}
		physics_->removeCollider((*i)->getCollider());
		physics_->removeBody((*i));
		i = simObjects_.erase(i);
	}
	simObjects_.clear();

	

	std::vector<Poison*> poison(NO_OF_POISON);
	for (Poison* p : poison) {
		p = new Poison();
		addNewObject(p);
	}
	std::vector<Food*> food(NO_OF_FOOD);
	for (Food* f : food) {
		f = new Food();
		addNewObject(f);
	}

	if (generation_ <= 0) {


	std::vector<Organism*> organisms(POPULATION_SIZE);
	for (Organism* o : organisms) {
		o = new Organism();
		addNewObject(o);
	}

	}
	else {

		GeneticAlgorithm* GA = new GeneticAlgorithm(oldOrganisms_);	
		std::vector<Organism*> newOrganisms = GA->createNewPopulation();
		for (Organism* o : newOrganisms) {
			addNewObject(o);
		}
		oldOrganisms_.clear();
	}

	CreateWallColliders();

	simTime_ = 0;

}

void EvolutionSimulation::CreateWallColliders()
{
	Collider* leftWallC = new Collider(Collider::Shapes::BOX, Collider::Types::WALL, 20.0f, 720.0f);
	Wall* leftWall = new Wall(leftWallC,Vector2f(0.0f,360.0f));
	addNewObject(leftWall);

	Collider* rightWallC = new Collider(Collider::Shapes::BOX, Collider::Types::WALL, 20.0f, 720.0f);
	Wall* rightWall = new Wall(rightWallC, Vector2f(1280.0f, 360));
	addNewObject(rightWall);

	Collider* topWallC = new Collider(Collider::Shapes::BOX, Collider::Types::WALL, 1280.0f,20.0f);
	Wall* topWall = new Wall(topWallC, Vector2f(640.0f, 720.0f));
	addNewObject(topWall);

	Collider* bottomWallC = new Collider(Collider::Shapes::BOX, Collider::Types::WALL, 1280.0f, 20.0f);
	Wall* bottomWall = new Wall(bottomWallC, Vector2f(640.0f, 0.0f));
	addNewObject(bottomWall);
}
