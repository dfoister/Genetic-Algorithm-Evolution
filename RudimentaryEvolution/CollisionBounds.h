#define _USE_MATH_DEFINES
#include <cmath>
#include <tuple>
#include <string>
#include <Eigen/Dense>

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
		PLAYER,
		GUARD,
		SPELL,
		PIXIE,
		FROGGO,
		FRUIT,
		MAP,
		LADDER,
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

	float vectorLength(Vector2f v);
	Vector2f normalizedVec(Vector2f v);

	std::tuple<bool, float, Vector2f> isCollided(CollisionBounds* col);

};

