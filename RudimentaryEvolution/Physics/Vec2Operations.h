#ifndef VEC2_OPERATIONS_H
#define VEC2_OPERATIONS_H
#include <../../Common/eigen-3.3.9/Eigen/Dense>

using Eigen::Vector2f;

class Vec2Operations
{
public:
	static inline Vector2f normalized(Vector2f v)
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
	};

	static inline float length(Vector2f v)
	{
		return sqrt((v.x() * v.x()) + (v.y() * v.y()));
	};

};

#endif

