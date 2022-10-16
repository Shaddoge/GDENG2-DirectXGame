#include "GameObject.h"

GameObject::GameObject(string name)
{
	this->name = name;
	this->local_position = Vector3();
	this->local_scale = Vector3(1.0f, 1.0f, 1.0f);
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
	this->local_position = Vector3(x, y, z);
}

void GameObject::SetPosition(Vector3 pos)
{
	this->local_position = pos;
}

void GameObject::SetPositionMouse(Vector2 delta_pos)
{
	delta_pos *= transform_speed;
	this->local_position = Vector3(local_position.x + delta_pos.x, local_position.y + delta_pos.y, local_position.z);
}

Vector3 GameObject::GetLocalPosition()
{
	return this->local_position;
}

void GameObject::SetScale(float x, float y, float z)
{
	this->local_scale = Vector3(x, y, z);
}

void GameObject::SetScale(Vector3 scale)
{
	this->local_scale = scale;
}

void GameObject::SetScaleMouse(Vector2 delta_pos)
{
	delta_pos *= transform_speed;
	this->local_scale = Vector3(local_scale.x + delta_pos.x, local_scale.y + delta_pos.y, local_scale.z);
}

Vector3 GameObject::GetLocalScale()
{
	return this->local_scale;
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


Vector3 GameObject::GetLocalRotation()
{
	return this->local_rotation;
}

VertexBuffer GameObject::GetVertexBuffer()
{
	return *m_vb;
}
