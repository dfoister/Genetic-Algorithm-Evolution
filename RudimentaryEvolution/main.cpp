#include "EvolutionSimulation.h"
#include "Constants.h"
#include <iostream>

int main()
{
	using namespace GLOBAL;

	std::cout << "Population Size: ";
	std::cin >> POPULATION_SIZE;
	std::cout << "\n";
	std::cout << "Amount of Food: ";
	std::cin >> NO_OF_FOOD;
	std::cout << "\n";
	std::cout << "Amount of Poison: ";
	std::cin >> NO_OF_POISON;
	std::cout << "\n";
	std::cout << "Generation Time in Seconds: ";
	std::cin >> GENERATION_TIME_IN_SECONDS;
	std::cout << "\n";
	std::cout << "Population Survivors (% of population): ";
	std::cin >> SURVIVOR_PERCENTAGE;
	std::cout << "\n";
	std::cout << "Selection Type (Roulette = 0) (Random = 1) (Tournament = 2): ";
	std::cin >> SELECTION_TYPE;

	if (SELECTION_TYPE == 2) {
		std::cout << "\n";
		std::cout << "Tournament Size: ";
		std::cin >> TOURNAMENT_SIZE;
		std::cout << "\n";
		std::cout << "Tournament Survivors: ";
		std::cin >> TOURNAMENT_SURVIVORS;
	}

	std::cout << "\n";
	std::cout << "Crossover Type (Uniform = 0) (Single-Point = 1) (Multi-Point = 2): ";
	std::cin >> CROSSOVER_TYPE;
	std::cout << "\n";
	std::cout << "Primary Mutation Type (Creep = 0) (Random Resetting = 1): ";
	std::cin >> MUTATION_TWO_TYPE;
	std::cout << "\n";

	if (MUTATION_TWO_TYPE == 0) {
		std::cout << "Creep Value Range: ";
		std::cin >> CREEP_RANGE;
		std::cout << "\n";
	}

	if (MUTATION_TWO_TYPE == 1) {
		std::cout << "Random Reset Lower Bound: ";
		std::cin >> RAND_LOWER;
		std::cout << "\n";
		std::cout << "Random Reset Upper Bound: ";
		std::cin >> RAND_UPPER;
		std::cout << "\n";
	}

	std::cout << "Secondary Mutation Type (None = 0) (Swap = 1) (Scramble = 2) (Inversion = 3): ";
	std::cin >> MUTATION_ONE_TYPE;
	std::cout << "\n";
	std::cout << "Mutation Chance Percentage (0.0f - 100.0f): ";
	std::cin >> MUTATION_CHANCE;
	std::cout << "\n";


	Rendering* r = new Rendering();

	r->window.create(sf::VideoMode(1280, 720), "Evolution Simulation!");
	r->window.setFramerateLimit(FRAMERATE_LIMIT);
	


	EvolutionSimulation* sim = new EvolutionSimulation(r);

	sf::Clock clock;
	clock.restart();
	float cycle = 0;
	while (r->window.isOpen())
	{

		sf::Time elapsed = clock.restart();
		

		if (elapsed.asSeconds() > 1.5f) continue;
		

		sf::Event event;
		while (r->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				r->window.close();
		}

		

		r->window.clear(sf::Color(192, 192, 192));

		if (cycle < GLOBAL::GENERATION_TIME_IN_SECONDS) {
			sim->update(elapsed.asSeconds());

		}
		else {
			sim->InitialiseSim();
			cycle = 0.0f;
		}
		
		r->window.display();
		cycle += elapsed.asSeconds();
	}

	return 0;
}

