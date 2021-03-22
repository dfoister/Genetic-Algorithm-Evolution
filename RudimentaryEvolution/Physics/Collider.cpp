#define _USE_MATH_DEFINES
#define NOMINMAX 
#include "Collider.h"
#include <algorithm>


Collider::Shapes Collider::getShape()
{
	return colliderShape_;
}

float Collider::getMinExtentX()
{
	return minExtentX_;
}

float Collider::getMaxExtentX()
{
	return maxExtentX_;
}

RigidBody* Collider::getObject()
{
	return object_;
}

void Collider::setObject(RigidBody* object)
{
	this->object_ = object;
}

void Collider::setColour(sf::Color colour)
{
	this->colour_ = colour;
}

sf::Color Collider::getColour()
{
	return colour_;
}

std::string Collider::getName()
{
	if (colliderType_ == Types::ORGANISM) return "ORGANISM";
	if (colliderType_ == Types::WALL) return "WALL";
	if (colliderType_ == Types::FOOD) return "FOOD";
	if (colliderType_ == Types::POISON) return "POISON";

	return "UNKNOWN";

}

Collider::Types Collider::getType()
{
	return colliderType_;
}
Collider::Collider()
{
	this->colliderType_ = Types::UNKNOWN;
	this->area_ = 0.0f;
	this->width_ = 0;
	this->height_ = 0;
	this->radius_ = 0;
	this->colliderShape_ = Shapes::UNKNOWN;
	this->position_ = Vector2f(0, 0);
	this->minExtentX_ = 0;
	this->maxExtentX_ = 0;

}

Collider::Collider(Collider::Shapes colShape, Collider::Types type, float width, float height)
{
	this->colliderType_ = type;
	this->area_ = width * height;
	this->radius_ = 0;
	this->width_ = width;
	this->height_ = height;
	this->colliderShape_ = colShape;
	this->position_ = Vector2f(0, 0);
	this->minExtentX_ = 0;
	this->maxExtentX_ = 0;

}

Collider::Collider(Collider::Shapes colShape, Collider::Types type, float radius)
{
	this->colliderType_ = type;
	this->area_ = static_cast <float> (M_PI * pow(radius, 2));
	this->radius_ = radius;
	this->width_ = radius * 2;
	this->height_ = width_;
	this->colliderShape_ = colShape;
	this->position_ = Vector2f(0, 0);
	this->minExtentX_ = 0;
	this->maxExtentX_ = 0;

}

Collider::~Collider()
{
}

float Collider::getArea()
{
	return area_;
}


float Collider::getWidth()
{
	return width_;
}

float Collider::getHeight()
{
	return height_;
}

float Collider::getRadius()
{
	return radius_;
}
void Collider::setPosition(Vector2f pos_)
{
	this->position_ = pos_;
	this->minExtentX_ = position_.x() - (width_ / 2);
	this->maxExtentX_ = position_.x() + (width_ / 2);
}



Vector2f Collider::getPosition()
{
	return position_;
}

std::tuple<bool, float, Vector2f> Collider::isCollided(Collider* col)
{


	if (Collider::colliderShape_ == Collider::Shapes::BOX) {


		if (col->getShape() == Collider::Shapes::BOX) {


			// Top Left of Shape 1
			float topLeftX = position_.x() - width_ / 2;
			float topLeftY = position_.y() - height_ / 2;

			// Top Left of Shape 2
			float topLeftX2 = col->getPosition().x() - col->getWidth() / 2;
			float topLeftY2 = col->getPosition().y() - col->getHeight() / 2;


			// If Collided
			if (topLeftX + width_ > topLeftX2 &&
				topLeftX < topLeftX2 + col->getWidth() &&
				topLeftY + height_ > topLeftY2 &&
				topLeftY < topLeftY2 + col->getHeight()) {

				float xPenetration = 0;
				float yPenetration = 0;
				Vector2f normal_;
				float penetration;

				//Calculate Penetration Distance and Collison Normal

				if (position_.x() < col->getPosition().x()) {
					xPenetration = -1 * ((position_.x() + width_ / 2) - (col->getPosition().x() - col->getWidth() / 2));
				}

				else if (position_.x() > col->getPosition().x()) {
					xPenetration = ((col->getPosition().x() + col->getWidth() / 2) - (position_.x() - width_ / 2));
				}

				if (position_.y() < col->getPosition().y()) {
					yPenetration = -1 * ((position_.y() + height_ / 2) - (col->getPosition().y() - col->getHeight() / 2));
				}

				else if (position_.y() > col->getPosition().y()) {
					yPenetration = ((col->getPosition().y() + col->getHeight() / 2) - (position_.y() - height_ / 2));
				}

				if (abs(xPenetration) < abs(yPenetration)) {
					normal_ = Vector2f(0, 1);
					penetration = xPenetration;
				}
				else {
					normal_ = Vector2f(1, 0);
					penetration = yPenetration;
				}

				return std::make_tuple(true, penetration, normal_);

			}
			else {
				// No Collision
				return std::make_tuple(false, 0.0f, Vector2f(0, 0));
			}
		}


		else if (col->getShape() == Collider::Shapes::CIRCLE) {
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


			Vector2f halfBox = Vector2f(width_ / 2, height_ / 2);
			Vector2f delta = col->getPosition() - position_;

			float closestX = std::clamp(delta.x(), -halfBox.x(), halfBox.x());
			float closestY = std::clamp(delta.y(), -halfBox.y(), halfBox.y());
			Vector2f closestPoint = Vector2f(closestX, closestY);

			Vector2f localPoint = delta - closestPoint;

			float distance = BasicVector2Operations::length(localPoint);

			if (distance < col->getRadius()) {
				Vector2f normal_ = BasicVector2Operations::normalized(localPoint);
				Vector2f normalReversed = Vector2f(-normal_.y(), normal_.x());
				float penetration = (col->getRadius() - distance);

				//std::cout << penetration << "  +  " << normal_ << "\n";
				return std::make_tuple(true, penetration, -normal_);
			}
			return std::make_tuple(false, 0.0f, Vector2f(0, 0));
		}



	}

	else if (Collider::colliderShape_ == Collider::Shapes::CIRCLE) {



		if (col->getShape() == Collider::Shapes::CIRCLE) {

			float radii = radius_ + col->getRadius();
			Vector2f delta = (col->getPosition() - position_);
			float deltaLength = BasicVector2Operations::length(delta);

			if (deltaLength < radii) {

				float pen = (radii - deltaLength);
				Vector2f normal_ = BasicVector2Operations::normalized(delta);
				return std::make_tuple(true, pen, normal_);


			}
			else {
				return std::make_tuple(false, 0.0f, Vector2f(0, 0));
			}
		}

		else if (col->getShape() == Collider::Shapes::BOX) {

			return col->isCollided(this);

		}
	}
	return std::make_tuple(false, 0.0f, Vector2f(0, 0));
}
