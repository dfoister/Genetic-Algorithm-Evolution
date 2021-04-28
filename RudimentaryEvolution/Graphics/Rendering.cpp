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

void Rendering::DrawOrganism(sf::Vector2f pos, float radius, sf::Color colour)
{
	sf::CircleShape o(radius);

	o.setPosition(pos);
	o.setOrigin(sf::Vector2f(radius, radius));
	o.setOutlineColor(colour);
	o.setOutlineThickness(2);
	o.setFillColor(sf::Color(192, 192, 192));

	window.draw(o);

}

void Rendering::DrawText(sf::Vector2f pos, std::string text)
{
	sf::Text t;
	sf::Font f;
	f.loadFromFile("Textures/ArialCE.ttf");
	t.setFont(f);
	t.setCharacterSize(15);
	t.setString(text);
	t.setPosition(sf::Vector2f(pos.x, pos.y));
	t.setFillColor(sf::Color::Black);

	window.draw(t);
}
