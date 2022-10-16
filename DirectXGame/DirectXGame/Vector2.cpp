#include "Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2::~Vector2()
{
}

void Vector2::operator+=(const Vector2& vector)
{
	Vector2 out;

	x += vector.x;
	y += vector.y;
}

void Vector2::operator*=(const float& value)
{
	x *= value;
	y *= value;
}