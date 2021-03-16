#define _USE_MATH_DEFINES
#include <cmath>
#include <tuple>
#include <string>
#include <../../Common/eigen-3.3.9/Eigen/Dense>
#include "BasicVector2Operations.h"

using Eigen::Vector2f;

class CollisionBounds
{
protected:
	float area;
	Vector2f position;
	float radius;
	float width;
	float height;
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
	Types type;
	Types getType();
	Shapes shape;
	Shapes getShape();

	float minExtentX;
	float maxExtentX;
	float getMinExtentX();
	float getMaxExtentX();

	std::string getName();
	CollisionBounds();
	CollisionBounds(CollisionBounds::Shapes shape, CollisionBounds::Types type, float width, float height);
	CollisionBounds(CollisionBounds::Shapes shape, CollisionBounds::Types type, float radius);
	~CollisionBounds();
	float getArea();
	float getWidth();
	float getHeight();
	float getRadius();
	void setPosition(Vector2f pos);
	Vector2f getPosition();

	std::tuple<bool, float, Vector2f> isCollided(CollisionBounds* col);

};

