#pragma once
#include "Matrix4x4.h"
#include "Vector3D.h"
#include "Vector2D.h"

/*
struct mat4
{
	float mat[4][4];
};*/

struct vertex
{
	Vector3D position;
	Vector2D texcoord;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_projection;
	float m_angle;
};