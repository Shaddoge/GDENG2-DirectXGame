#include "GameObject.h"

GameObject::GameObject(string name)
{
	this->name = name;
	this->world_position = Vector3();
	this->scale = Vector3(1.0f, 1.0f, 1.0f);
	this->local_rotation = Vector3();
}

GameObject::~GameObject()
{
}

void GameObject::Update(float delta_time)
{
}

void GameObject::Draw(int width, int height)
{
}

void GameObject::SetPosition(float x, float y, float z)
{
	this->world_position = Vector3(x, y, z);
}

void GameObject::SetPosition(Vector3 pos)
{
	this->world_position = pos;
}

void GameObject::SetPositionMouse(Vector2 delta_pos)
{
	delta_pos *= transform_speed;
	this->world_position = Vector3(world_position.x + delta_pos.x, world_position.y + delta_pos.y, world_position.z);
}

void GameObject::SetPositionZMouse(Vector2 delta_pos)
{
	delta_pos *= transform_speed;
	this->world_position = Vector3(world_position.x, world_position.y, world_position.z + delta_pos.x);
}

Vector3 GameObject::GetWorldPosition()
{
	return this->world_position;
}

void GameObject::SetScale(float x, float y, float z)
{
	this->scale = Vector3(x, y, z);
}

void GameObject::SetScale(Vector3 scale)
{
	this->scale = scale;
}

void GameObject::SetScaleMouse(Vector2 delta_pos)
{
	delta_pos *= transform_speed;
	this->scale = Vector3(scale.x + delta_pos.x, scale.y + delta_pos.y, scale.z);
}

void GameObject::SetScaleZMouse(Vector2 delta_pos)
{
	delta_pos *= transform_speed;
	this->scale = Vector3(scale.x, scale.y, scale.z + delta_pos.x);
}

Vector3 GameObject::GetScale()
{
	return this->scale;
}

void GameObject::SetRotation(float x, float y, float z)
{
	this->local_rotation = Vector3(x, y, z);
}

void GameObject::SetRotation(Vector3 rot)
{
	this->local_rotation = rot;
}

void GameObject::SetRotationMouse(Vector2 delta_pos)
{
	delta_pos *= transform_speed;
	this->local_rotation = Vector3(local_rotation.x + delta_pos.y, local_rotation.y - delta_pos.x, local_rotation.z);
}

void GameObject::SetRotationZMouse(Vector2 delta_pos)
{
	delta_pos *= transform_speed;
	this->local_rotation = Vector3(local_rotation.x, local_rotation.y, local_rotation.z - delta_pos.x);
}

Vector3 GameObject::GetLocalRotation()
{
	return this->local_rotation;
}