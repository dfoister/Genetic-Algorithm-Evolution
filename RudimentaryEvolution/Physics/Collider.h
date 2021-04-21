#define _USE_MATH_DEFINES
#include <cmath>
#include <tuple>
#include <string>
#include <Eigen/Dense>
#include "Vec2Operations.h"
#include <Graphics/Color.hpp>

using Eigen::Vector2f;

class RigidBody;
class Collider
{
protected:
	float area_;
	Vector2f position_;
	float radius_;
	float width_;
	float height_;
	sf::Color colour_;
	RigidBody* object_;
public:
	enum class Shapes {
		BOX,
		CIRCLE,
		UNKNOWN
	};
	enum class Types {
		ORGANISM,
		FOOD,
		POISON,
		WALL,
		UNKNOWN
	};
	Types colliderType_;
	Types getType();
	Shapes colliderShape_;
	Shapes getShape();

	float minExtentX_;
	float maxExtentX_;
	float getMinExtentX();
	float getMaxExtentX();

	RigidBody* getObject();
	void setObject(RigidBody* o);

	void setColour(sf::Color colour);
	sf::Color getColour();

	std::string getName();
	Collider();
	Collider(Collider::Shapes shape, Collider::Types type, float width, float height);
	Collider(Collider::Shapes shape, Collider::Types type, float radius);
	~Collider();
	float getArea();
	float getWidth();
	float getHeight();
	float getRadius();
	void setPosition(Vector2f pos_);
	Vector2f getPosition();

	std::tuple<bool, float, Vector2f> isCollided(Collider* col);

};

