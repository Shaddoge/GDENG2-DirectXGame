#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include <iostream>

class Camera
{
public:
	Camera();
	~Camera();
public:
	void Update(float delta_time);
	Matrix GetInverseWorldCam();
	void SetForward(float value);
	void SetRotationMouse(Vector2 delta_pos);
private:
	float translate_speed = 0.035f;
	float look_speed = 0.5f;
	float forward = 0.0f;
	Matrix world_cam;
	Vector3 rotation;
};