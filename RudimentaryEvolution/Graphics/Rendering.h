#include <vector>
#include <Graphics.hpp>

class BaseObject;
class Rendering
{
public: 
	Rendering();
	~Rendering();

	sf::RenderWindow window;

	void DrawCircle(sf::Vector2f pos, float radius, sf::Color colour);
	void DrawBox(sf::Vector2f pos, float width, float height, sf::Color colour);

protected:

	std::vector<BaseObject*> allObjects;
};

