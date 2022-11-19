#pragma once
class Vector3D
{
public:
	Vector3D();
	Vector3D(float _x, float _y, float _z);
	~Vector3D();
public:
	void operator+=(const Vector3D& vector);
	void operator*=(const Vector3D& vector);
	void operator*=(const float value);
	Vector3D operator*(const float value);
	Vector3D operator+(const Vector3D& vector);
	Vector3D lerp(const Vector3D& a, const Vector3D& b, float delta);

	static Vector3D zeros();
	static Vector3D ones();
public:
	float x, y, z;
};

