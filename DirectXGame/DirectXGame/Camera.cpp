#include "Camera.h"
#include <stdio.h>
Camera::Camera(string name) : GameObject(name)
{
	// Initialize position and rotation of camera
	SetRotation(Vector3(0.5f, -0.9f, 0.0f));
	world_cam.SetTranslate(Vector3(5.0, 3.5f, -2.5f));
}

Camera::~Camera()
{
}

void Camera::Update(float delta_time)
{
	Matrix new_world_cam;
	new_world_cam.SetIdentity();

	Matrix temp;
	Vector3 local_rotation = GetLocalRotation();
	temp.SetIdentity();
	temp.SetRotationX(local_rotation.x);
	new_world_cam *= temp;

	temp.SetIdentity();
	temp.SetRotationY(local_rotation.y);
	new_world_cam *= temp;

	// Forward
	Vector3 new_pos = world_cam.GetTranslation() + world_cam.GetZDirection() * (forward * translate_speed);
	// Right
	new_pos = new_pos + world_cam.GetXDirection() * (right * translate_speed);
	// Top
	new_pos = new_pos + world_cam.GetYDirection() * (top * translate_speed);
	new_world_cam.SetTranslate(new_pos);

	world_cam = new_world_cam;
}

Matrix Camera::GetInverseWorldCam()
{
	Matrix inverse_world_cam = world_cam;
	inverse_world_cam.Inverse();
	return inverse_world_cam;
}

void Camera::SetForward(float value)
{
	forward = value;
}

void Camera::SetRight(float value)
{
	right = value;
}

void Camera::SetTop(float value)
{
	top = value;
}

void Camera::SetRotationMouse(Vector2 delta_pos)
{
	delta_pos *= look_speed;
	Vector3 local_rotation = GetLocalRotation();
	SetRotation(Vector3(local_rotation.x - delta_pos.y, local_rotation.y + delta_pos.x, local_rotation.z));
}