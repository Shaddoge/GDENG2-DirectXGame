#include "Vector3.h"

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3::~Vector3()
{
}

void Vector3::operator+=(const Vector3& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
}

void Vector3::operator*=(const Vector3& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
}

void Vector3::operator*=(const float value)
{
	x *= value;
	y *= value;
	z *= value;
}


Vector3 Vector3::operator*(const float value)
{
	return Vector3(x * value, y * value, z * value);
}

Vector3 Vector3::operator+(const Vector3& vector)
{
	return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

Vector3 Vector3::lerp(const Vector3& a, const Vector3& b, float delta)
{
	Vector3 lerped = {
		a.x + delta * (b.x - a.x),
		a.y + delta * (b.y - a.y),
		a.z + delta * (b.z - a.z),
	};

	return lerped;
}
