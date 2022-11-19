#include "Camera.h"
#include <stdio.h>
Camera::Camera(String name) : GameObject(name, GameObject::PrimitiveType::CAMERA)
{
	// Initialize position and rotation of camera
	//SetRotation(Vector3D(0.5f, -0.9f, 0.0f));
	//world_cam.SetTranslate(Vector3D(5.0, 3.5f, -2.5f));
	world_cam.SetTranslate(Vector3D(0.0, 0.5f, -2.5f));
}

Camera::~Camera()
{
}

void Camera::Update(float delta_time)
{
	Matrix4x4 new_world_cam;
	new_world_cam.SetIdentity();

	Matrix4x4 temp;
	Vector3D local_rotation = GetLocalRotation();
	temp.SetIdentity();
	temp.SetRotationX(local_rotation.x);
	new_world_cam *= temp;

	temp.SetIdentity();
	temp.SetRotationY(local_rotation.y);
	new_world_cam *= temp;

	// Forward
	Vector3D new_pos = world_cam.GetTranslation() + world_cam.GetZDirection() * (forward * translate_speed);
	// Right
	new_pos = new_pos + world_cam.GetXDirection() * (right * translate_speed);
	// Top
	new_pos = new_pos + world_cam.GetYDirection() * (top * translate_speed);
	new_world_cam.SetTranslate(new_pos);

	world_cam = new_world_cam;
}

Matrix4x4 Camera::GetViewMatrix()
{
	return Matrix4x4();
}

Matrix4x4 Camera::GetInverseWorldCam()
{
	Matrix4x4 inverse_world_cam = world_cam;
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

void Camera::SetRotationMouse(Vector2D delta_pos)
{
	delta_pos *= look_speed;
	Vector3D local_rotation = GetLocalRotation();
	SetRotation(Vector3D(local_rotation.x - delta_pos.y, local_rotation.y + delta_pos.x, local_rotation.z));
}

void Camera::UpdateViewMatrix()
{
	Matrix4x4 worldCam; worldCam.SetIdentity();
	Matrix4x4 temp; temp.SetIdentity();

	Vector3D localRot = this->GetLocalRotation();

	temp.SetRotationX(localRot.x);
	worldCam = worldCam.MultiplyTo(temp);

	temp.SetRotationY(localRot.y);
	worldCam = worldCam.MultiplyTo(temp);

	temp.SetTranslate(this->GetLocalPosition());
	worldCam = worldCam.MultiplyTo(temp);

	worldCam.Inverse();
	this->localMatrix = worldCam;
}
