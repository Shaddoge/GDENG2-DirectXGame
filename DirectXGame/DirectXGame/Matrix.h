#pragma once
#include "Vector3.h"
#include <iostream>

class Matrix
{
public:
	Matrix() {};
	~Matrix() {};
public:
	void SetIdentity();
	void SetTranslate(Vector3 vector);
	void SetScale(Vector3 vector);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);
	void SetMatrix(const Matrix matrix);
	void SetOrthoLH(float width, float height, float near_plane, float far_plane);
public:
	void operator *=(const Matrix& matrix);
public:
	float mat[4][4] = {};
};