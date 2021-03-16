#include "Rendering.h"

Rendering::Rendering()
{
}

Rendering::~Rendering()
{
}

void Rendering::DrawCircle(sf::Vector2f pos, float radius, sf::Color colour)
{
	sf::CircleShape circle(radius);

	circle.setPosition(pos);
	circle.setOrigin(sf::Vector2f(radius, radius));
	circle.setFillColor(colour);

	window.draw(circle);

	
}

void Rendering::DrawBox(sf::Vector2f pos, float width, float height, sf::Color colour)
{

	sf::RectangleShape rect(sf::Vector2f(width,height));

	rect.setPosition(pos);
	rect.setOrigin(sf::Vector2f(width / 2, height / 2));
	rect.setFillColor(colour);

	window.draw(rect);
}
