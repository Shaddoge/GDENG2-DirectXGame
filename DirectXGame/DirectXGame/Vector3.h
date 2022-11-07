#pragma once
class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z);
	~Vector3();
public:
	void operator+=(const Vector3& vector);
	void operator*=(const Vector3& vector);
	void operator*=(const float value);
	Vector3 operator*(const float value);
	Vector3 operator+(const Vector3& vector);
	Vector3 lerp(const Vector3& a, const Vector3& b, float delta);
public:
	float x, y, z;
};

