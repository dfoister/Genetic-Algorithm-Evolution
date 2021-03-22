#include "EvolutionSimulation.h"
#include "Constants.h"

int main()
{
	Rendering* r = new Rendering();

	r->window.create(sf::VideoMode(1280, 720), "bonk!");
	r->window.setFramerateLimit(constants::FRAMERATE_LIMIT);
	
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

		

		r->window.clear(sf::Color(192,192,192));
		sim->update(elapsed.asSeconds());
		r->window.display();
	}

	return 0;
}
