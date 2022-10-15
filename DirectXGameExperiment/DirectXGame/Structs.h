#pragma once
#include "Matrix.h"

/*
struct mat4
{
	float mat[4][4];
};*/

__declspec(align(16))
struct constant
{
	Matrix m_world;
	Matrix m_view;
	Matrix m_projection;
	float m_angle;
};