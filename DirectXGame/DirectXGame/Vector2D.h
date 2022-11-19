#pragma once
class Vector2D
{
public:
	Vector2D();
	Vector2D(float _x, float _y);
	~Vector2D();
public:
	void operator += (const Vector2D& vector);
	void operator *= (const float& value);
	Vector2D operator*(const float value);
	Vector2D operator+(const Vector2D& vector);
public:
	float x;
	float y;
};