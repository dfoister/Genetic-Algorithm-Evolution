#include "EvolutionSimulation.h"
#include "Constants.h"
#include <iostream>

int main()
{
	std::cout << "Population Size: ";
	std::cin >> constants::POPULATION_SIZE;
	std::cout << "\n";
	std::cout << "Amount of Food: ";
	std::cin >> constants::NO_OF_FOOD;
	std::cout << "\n";
	std::cout << "Amount of Poison: ";
	std::cin >> constants::NO_OF_POISON;
	std::cout << "\n";
	std::cout << "Generation Time in Seconds: ";
	std::cin >> constants::GENERATION_TIME_IN_SECONDS;
	std::cout << "\n";
	std::cout << "Mutation Chance Percentage (0.0f - 100.0f): ";
	std::cin >> constants::MUTATION_CHANCE;
	std::cout << "\n";

	Rendering* r = new Rendering();

	r->window.create(sf::VideoMode(1280, 720), "bonk!");
	r->window.setFramerateLimit(constants::FRAMERATE_LIMIT);
	
	

	EvolutionSimulation* sim = new EvolutionSimulation(r);

	sf::Clock clock;
	clock.restart();

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

		

		r->window.clear(sf::Color(192,192,192));
		sim->update(elapsed.asSeconds());
		r->window.display();
	}

	return 0;
}
