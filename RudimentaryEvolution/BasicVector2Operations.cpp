#include "BasicVector2Operations.h"

Vector2f BasicVector2Operations::normalized(Vector2f v)
{
	if (length(v) != 0) {

		float tempLength = 1.0f / length(v);
		float tempX;
		float tempY;
		tempX = v.x() * tempLength;
		tempY = v.y() * tempLength;

		return Vector2f(tempX, tempY);
	}
	else {
		return Vector2f(0, 0);
	}
}

float BasicVector2Operations::length(Vector2f v)
{
    return sqrt((v.x() * v.x()) + (v.y() * v.y()));
}
