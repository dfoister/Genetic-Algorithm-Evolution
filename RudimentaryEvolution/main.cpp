#include "EvolutionSimulation.h"

int main()
{
	Rendering* r = new Rendering();

	r->window.create(sf::VideoMode(1280, 720), "bonk!");
	r->window.setFramerateLimit(30);
	
	sf::Clock clock;

	EvolutionSimulation* sim = new EvolutionSimulation(r);

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

		

		r->window.clear(sf::Color::White);
		sim->update(elapsed.asSeconds());
		r->window.display();
	}

	return 0;
}
