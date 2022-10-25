#pragma once
class Vector4
{
public:
	Vector4();
	Vector4(float _x, float _y, float _z, float _w);
	~Vector4();
public:
	void operator+=(const Vector4& vector);
	void operator*=(const Vector4& vector);
	void operator*=(const float value);
	void Cross(Vector4& v1, Vector4& v2, Vector4& v3);
public:
	float x, y, z, w;
};

