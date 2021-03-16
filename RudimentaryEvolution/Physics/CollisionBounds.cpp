#define _USE_MATH_DEFINES
#define NOMINMAX 
#include "CollisionBounds.h"
#include <algorithm>


CollisionBounds::Shapes CollisionBounds::getShape()
{
	return shape;
}

float CollisionBounds::getMinExtentX()
{
	return minExtentX;
}

float CollisionBounds::getMaxExtentX()
{
	return maxExtentX;
}

std::string CollisionBounds::getName()
{
	if (type == Types::ORGANISM) return "ORGANISM";
	if (type == Types::WALL) return "WALL";
	if (type == Types::FOOD) return "FOOD";
	if (type == Types::POISON) return "PIXIE";

	return "UNKNOWN";

}

CollisionBounds::Types CollisionBounds::getType()
{
	return type;
}
CollisionBounds::CollisionBounds()
{
	this->type = Types::UNKNOWN;
	this->area = 0.0f;
	this->width = 0;
	this->height = 0;
	this->radius = 0;
	this->shape = Shapes::UNKNOWN;
	this->position = Vector2f(0, 0);
	this->minExtentX = 0;
	this->maxExtentX = 0;

}

CollisionBounds::CollisionBounds(CollisionBounds::Shapes colShape, CollisionBounds::Types type, float width, float height)
{
	this->type = type;
	this->area = width * height;
	this->radius = 0;
	this->width = width;
	this->height = height;
	this->shape = colShape;
	this->position = Vector2f(0, 0);
	this->minExtentX = 0;
	this->maxExtentX = 0;

}

CollisionBounds::CollisionBounds(CollisionBounds::Shapes colShape, CollisionBounds::Types type, float radius)
{
	this->type = type;
	this->area = static_cast <float> (M_PI * pow(radius, 2));
	this->radius = radius;
	this->width = radius * 2;
	this->height = width;
	this->shape = colShape;
	this->position = Vector2f(0, 0);
	this->minExtentX = 0;
	this->maxExtentX = 0;

}

CollisionBounds::~CollisionBounds()
{
}

float CollisionBounds::getArea()
{
	return area;
}


float CollisionBounds::getWidth()
{
	return width;
}

float CollisionBounds::getHeight()
{
	return height;
}

float CollisionBounds::getRadius()
{
	return radius;
}
void CollisionBounds::setPosition(Vector2f pos)
{
	this->position = pos;
	this->minExtentX = position.x() - (width / 2);
	this->maxExtentX = position.x() + (width / 2);
}



Vector2f CollisionBounds::getPosition()
{
	return position;
}

std::tuple<bool, float, Vector2f> CollisionBounds::isCollided(CollisionBounds* col)
{


	if (CollisionBounds::shape == CollisionBounds::Shapes::BOX) {


		if (col->getShape() == CollisionBounds::Shapes::BOX) {


			// Top Left of Shape 1
			float topLeftX = position.x() - width / 2;
			float topLeftY = position.y() - height / 2;

			// Top Left of Shape 2
			float topLeftX2 = col->getPosition().x() - col->getWidth() / 2;
			float topLeftY2 = col->getPosition().y() - col->getHeight() / 2;


			// If Collided
			if (topLeftX + width > topLeftX2 &&
				topLeftX < topLeftX2 + col->getWidth() &&
				topLeftY + height > topLeftY2 &&
				topLeftY < topLeftY2 + col->getHeight()) {

				float xPenetration = 0;
				float yPenetration = 0;
				Vector2f normal;
				float penetration;

				//Calculate Penetration Distance and Collison Normal

				if (position.x() < col->getPosition().x()) {
					xPenetration = -1 * ((position.x() + width / 2) - (col->getPosition().x() - col->getWidth() / 2));
				}

				else if (position.x() > col->getPosition().x()) {
					xPenetration = ((col->getPosition().x() + col->getWidth() / 2) - (position.x() - width / 2));
				}

				if (position.y() < col->getPosition().y()) {
					yPenetration = -1 * ((position.y() + height / 2) - (col->getPosition().y() - col->getHeight() / 2));
				}

				else if (position.y() > col->getPosition().y()) {
					yPenetration = ((col->getPosition().y() + col->getHeight() / 2) - (position.y() - height / 2));
				}

				if (abs(xPenetration) < abs(yPenetration)) {
					normal = Vector2f(0, 1);
					penetration = xPenetration;
				}
				else {
					normal = Vector2f(1, 0);
					penetration = yPenetration;
				}

				return std::make_tuple(true, penetration, normal);

			}
			else {
				// No Collision
				return std::make_tuple(false, 0.0f, Vector2f(0, 0));
			}
		}


		else if (col->getShape() == CollisionBounds::Shapes::CIRCLE) {
#
			////////////////////////////////
			// ALTERNATE COLLISION METHOD //
			////////////////////////////////
			/*
			float circleX = col->getPosition().x();
			float circleY = col->getPosition().y();
			float positionx = position.x() - width/2;
			float positiony = position.y() - height / 2;

			float distX = abs(circleX - positionx - width / 2);
			float distY = abs(circleY - positiony - height / 2);

			if (distX > (width / 2 + col->getRadius())) return std::make_tuple(false, 0, Vector2f(0, 0));
			if (distY > (height / 2 + col->getRadius())) return std::make_tuple(false, 0, Vector2f(0, 0));

			if (distX <= (width / 2)) return std::make_tuple(true, 0, Vector2f(0, 0));
			if (distY <= (height / 2)) return std::make_tuple(true, 0, Vector2f(0, 0));

			float dx = distX - width / 2;
			float dy = distY - height / 2;

			bool result = (dx * dx + dy * dy <= (col->getRadius() * col->getRadius()));

			return std::make_tuple(result, 0, Vector2f(0, 0));


			*/
			////////////////////////////////
			// ALTERNATE COLLISION METHOD //
			////////////////////////////////

			/*
			// temporary variables to set edges for testing
			float testX = col->getPosition().x();
			float testY = col->getPosition().y();

			float rectangleX = position.x() - width / 2;
			float rectangleY = position.y() - height / 2;

			// which edge is closest?
			if (col->getPosition().x() < rectangleX)    testX = rectangleX;      // test left edge
			else if (col->getPosition().x() > rectangleX + width)    testX = rectangleX + width;   // right edge
			if (col->getPosition().y() < rectangleY)    testY = rectangleY;      // top edge
			else if (col->getPosition().y() > rectangleY + height)    testY = rectangleY + height;   // bottom edge

			// get distance from closest edges
			float distX = col->getPosition().x() - testX;
			float distY = col->getPosition().y() - testY;
			float distance = sqrt((distX * distX) + (distY * distY));

			// if the distance is less than the radius, collision!
			if (distance <= col->getRadius()) {
				return std::make_tuple(true, 0, Vector2f(0, 0));
			}
			else {
				return std::make_tuple(false, 0, Vector2f(0, 0));
			}

			*/


			Vector2f halfBox = Vector2f(width / 2, height / 2);
			Vector2f delta = col->getPosition() - position;

			float closestX = std::clamp(delta.x(), -halfBox.x(), halfBox.x());
			float closestY = std::clamp(delta.y(), -halfBox.y(), halfBox.y());
			Vector2f closestPoint = Vector2f(closestX, closestY);

			Vector2f localPoint = delta - closestPoint;

			float distance = BasicVector2Operations::length(localPoint);

			if (distance < col->getRadius()) {
				Vector2f normal = BasicVector2Operations::normalized(localPoint);
				float penetration = (col->getRadius() - distance);

				//std::cout << penetration << "  +  " << normal << "\n";
				return std::make_tuple(true, penetration, normal);
			}
			return std::make_tuple(false, 0.0f, Vector2f(0, 0));
		}



	}

	else if (CollisionBounds::shape == CollisionBounds::Shapes::CIRCLE) {



		if (col->getShape() == CollisionBounds::Shapes::CIRCLE) {

			float radii = radius + col->getRadius();
			Vector2f delta = (col->getPosition() - position);
			float deltaLength = BasicVector2Operations::length(delta);

			if (deltaLength < radii) {

				float pen = (radii - deltaLength);
				Vector2f normal = BasicVector2Operations::normalized(delta);
				return std::make_tuple(true, pen, normal);


			}
			else {
				return std::make_tuple(false, 0.0f, Vector2f(0, 0));
			}
		}

		else if (col->getShape() == CollisionBounds::Shapes::BOX) {

			return col->isCollided(this);

		}
	}
	return std::make_tuple(false, 0.0f, Vector2f(0, 0));
}
