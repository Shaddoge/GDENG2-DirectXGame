#include "Vector3D.h"

Vector3D::Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3D::Vector3D(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3D::~Vector3D()
{
}

void Vector3D::operator+=(const Vector3D& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
}

void Vector3D::operator*=(const Vector3D& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
}

void Vector3D::operator*=(const float value)
{
	x *= value;
	y *= value;
	z *= value;
}


Vector3D Vector3D::operator*(const float value)
{
	return Vector3D(x * value, y * value, z * value);
}

Vector3D Vector3D::operator+(const Vector3D& vector)
{
	return Vector3D(x + vector.x, y + vector.y, z + vector.z);
}

Vector3D Vector3D::lerp(const Vector3D& a, const Vector3D& b, float delta)
{
	Vector3D lerped = {
		a.x + delta * (b.x - a.x),
		a.y + delta * (b.y - a.y),
		a.z + delta * (b.z - a.z),
	};

	return lerped;
}

Vector3D Vector3D::zeros()
{
	return Vector3D(0.0f, 0.0f, 0.0f);
}

Vector3D Vector3D::ones()
{
	return Vector3D(1.0f, 1.0f, 1.0f);
}
