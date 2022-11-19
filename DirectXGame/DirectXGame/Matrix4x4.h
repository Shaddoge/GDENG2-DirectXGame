#pragma once
#include <memory>
#include "Vector3D.h"
#include "Vector4.h"
#include <iostream>

class Matrix4x4
{
public:
	Matrix4x4() {};
	~Matrix4x4() {};
public:
	void SetIdentity();
	void SetMatrix(const Matrix4x4 matrix);
	void SetMatrix(float matrix[4][4]);
	void SetTranslate(Vector3D vector);
	void SetScale(Vector3D vector);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);
	Vector3D GetZDirection();
	Vector3D GetYDirection();
	Vector3D GetXDirection();
	
	Vector3D GetTranslation();
	void SetPerspectiveFovLH(float fov, float aspect, float znear, float zfar);
	void SetOrthoLH(float width, float height, float near_plane, float far_plane);
	void Inverse();
	float GetDeterminant();

	Matrix4x4 MultiplyTo(Matrix4x4 matrix);
	float* GetMatrix();
public:
	void operator *=(const Matrix4x4& matrix);
public:
	float mat[4][4] = {};
};