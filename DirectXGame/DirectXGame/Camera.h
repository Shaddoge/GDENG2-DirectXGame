#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "GameObject.h"
#include <iostream>

class Camera : public GameObject
{
public:
	Camera(string name);
	~Camera();
public:
	void Update(float delta_time);
	Matrix GetInverseWorldCam();
	void SetForward(float value);
	void SetRight(float value);
	void SetTop(float value);
	virtual void SetRotationMouse(Vector2 delta_pos) override;
private:
	float translate_speed = 0.035f;
	float look_speed = 0.5f;
	float forward = 0.0f;
	float right = 0.0f;
	float top = 0.0f;
	Matrix world_cam;
};