#pragma once
#include <memory>
#include "Vector3.h"
#include "Vector4.h"
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
	Vector3 GetZDirection();
	Vector3 GetXDirection();
	Vector3 GetTranslation();
	void SetPerspectiveFovLH(float fov, float aspect, float znear, float zfar);
	void SetOrthoLH(float width, float height, float near_plane, float far_plane);
	void Inverse();
	float GetDeterminant();
public:
	void operator *=(const Matrix& matrix);
public:
	float mat[4][4] = {};
};