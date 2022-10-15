#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float _x, float _y);
	~Vector2();
public:
	void operator += (const Vector2& vector);
public:
	float x;
	float y;
};