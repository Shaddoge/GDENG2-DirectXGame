#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2D::~Vector2D()
{
}

void Vector2D::operator+=(const Vector2D& vector)
{
	Vector2D out;

	x += vector.x;
	y += vector.y;
}

void Vector2D::operator*=(const float& value)
{
	x *= value;
	y *= value;
}

Vector2D Vector2D::operator*(const float value)
{
	return Vector2D(x * value, y * value);
}

Vector2D Vector2D::operator+(const Vector2D& vector)
{
	return Vector2D(x + vector.x, y + vector.y);
}