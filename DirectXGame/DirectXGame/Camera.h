#pragma once
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "GameObject.h"
#include <iostream>

class Camera : public GameObject
{
public:
	Camera(String name);
	~Camera();
public:
	void Update(float delta_time);
	Matrix4x4 GetViewMatrix();

	Matrix4x4 GetInverseWorldCam();
	void SetForward(float value);
	void SetRight(float value);
	void SetTop(float value);
	virtual void SetRotationMouse(Vector2D delta_pos) override;
private:
	void UpdateViewMatrix();

	float translate_speed = 0.035f;
	float look_speed = 0.5f;
	float forward = 0.0f;
	float right = 0.0f;
	float top = 0.0f;
	Matrix4x4 world_cam;
};