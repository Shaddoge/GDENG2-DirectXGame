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
public:
	float x;
	float y;
	float z;
};

