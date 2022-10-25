#include "Camera.h"
#include <stdio.h>
Camera::Camera()
{
	world_cam.SetTranslate(Vector3(0, 0, -2));
}

Camera::~Camera()
{
}

void Camera::Update(float delta_time)
{
	Matrix new_world_cam;
	new_world_cam.SetIdentity();

	Matrix temp;
	temp.SetIdentity();
	temp.SetRotationX(rotation.x);
	new_world_cam *= temp;

	temp.SetIdentity();
	temp.SetRotationY(rotation.y);
	new_world_cam *= temp;

	Vector3 new_pos = world_cam.GetTranslation() + world_cam.GetZDirection() * (forward * translate_speed);
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

void Camera::SetRotationMouse(Vector2 delta_pos)
{
	delta_pos *= look_speed;
	this->rotation = Vector3(rotation.x - delta_pos.y, rotation.y + delta_pos.x, rotation.z);
}