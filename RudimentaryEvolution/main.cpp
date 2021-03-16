#include "EvolutionSimulation.h"
#include <Graphics.hpp>
#include <vector>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "bonk!");;
	window.setFramerateLimit(30);
	
	sf::Clock clock;

	unsigned int windowWidth = window.getSize().x;
	unsigned int windowHeight = window.getSize().y;

	EvolutionSimulation* sim = new EvolutionSimulation();

	clock.restart();

	while (window.isOpen())
	{

		sf::Time elapsed = clock.restart();
		if (elapsed.asSeconds() > 1.5f) continue;
		sim->update(elapsed.asSeconds());
		



		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		window.clear(sf::Color::White);
		window.display();
	}

	return 0;
}
