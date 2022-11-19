#include "GameObject.h"

GameObject::GameObject(String name, PrimitiveType type)
{
	this->name = name;
	this->objectType = type;
	this->local_rotation = Vector3D();
	this->local_position = Vector3D::zeros();
	this->local_scale = Vector3D::ones();
	this->localMatrix.SetIdentity();
}

GameObject::~GameObject()
{
}

GameObject::PrimitiveType GameObject::GetObjectType()
{
	return this->objectType;
}

void GameObject::Update(float delta_time)
{
}

void GameObject::Draw(int width, int height)
{
}

void GameObject::SetPosition(float x, float y, float z)
{
	this->local_position = Vector3D(x, y, z);
}

void GameObject::SetPosition(Vector3D pos)
{
	this->local_position = pos;
}

void GameObject::SetPositionMouse(Vector2D delta_pos)
{
	delta_pos *= transform_speed;
	this->local_position = Vector3D(local_position.x + delta_pos.x, local_position.y + delta_pos.y, local_position.z);
}

void GameObject::SetPositionZMouse(Vector2D delta_pos)
{
	delta_pos *= transform_speed;
	this->local_position = Vector3D(local_position.x, local_position.y, local_position.z + delta_pos.x);
}

Vector3D GameObject::GetLocalPosition()
{
	return this->local_position;
}

void GameObject::SetScale(float x, float y, float z)
{
	this->local_scale = Vector3D(x, y, z);
}

void GameObject::SetScale(Vector3D local_scale)
{
	this->local_scale = local_scale;
}

void GameObject::SetScaleMouse(Vector2D delta_pos)
{
	delta_pos *= transform_speed;
	this->local_scale = Vector3D(local_scale.x + delta_pos.x, local_scale.y + delta_pos.y, local_scale.z);
}

void GameObject::SetScaleZMouse(Vector2D delta_pos)
{
	delta_pos *= transform_speed;
	this->local_scale = Vector3D(local_scale.x, local_scale.y, local_scale.z + delta_pos.x);
}

Vector3D GameObject::GetLocalScale()
{
	return this->local_scale;
}

void GameObject::SetRotation(float x, float y, float z)
{
	this->local_rotation = Vector3D(x, y, z);
}

void GameObject::SetRotation(Vector3D rot)
{
	this->local_rotation = rot;
}

void GameObject::SetRotationMouse(Vector2D delta_pos)
{
	delta_pos *= transform_speed;
	this->local_rotation = Vector3D(local_rotation.x + delta_pos.y, local_rotation.y - delta_pos.x, local_rotation.z);
}

void GameObject::SetRotationZMouse(Vector2D delta_pos)
{
	delta_pos *= transform_speed;
	this->local_rotation = Vector3D(local_rotation.x, local_rotation.y, local_rotation.z - delta_pos.x);
}

Vector3D GameObject::GetLocalRotation()
{
	return this->local_rotation;
}

String GameObject::GetName()
{
	return this->name;
}

bool GameObject::IsEnabled()
{
	return this->enabled;
}

void GameObject::SetEnabled(bool flag)
{
	this->enabled = flag;
}

float* GameObject::GetPhysicsLocalMatrix()
{
	Matrix4x4 allMatrix;
	allMatrix.SetIdentity();

	Matrix4x4 translationMatrix;
	translationMatrix.SetIdentity();
	translationMatrix.SetTranslate(this->GetLocalPosition());
	Matrix4x4 scaleMatrix;
	scaleMatrix.SetScale(Vector3D::ones());
	Vector3D rotation = this->GetLocalRotation();

	Matrix4x4 xMatrix;
	xMatrix.SetRotationX(rotation.x);
	Matrix4x4 yMatrix;
	yMatrix.SetRotationY(rotation.y);
	Matrix4x4 zMatrix;
	zMatrix.SetRotationZ(rotation.z);

	Matrix4x4 rotMatrix; rotMatrix.SetIdentity();
	rotMatrix = rotMatrix.MultiplyTo(xMatrix.MultiplyTo(yMatrix.MultiplyTo(zMatrix)));

	allMatrix = allMatrix.MultiplyTo(scaleMatrix.MultiplyTo(rotMatrix));
	allMatrix = allMatrix.MultiplyTo(translationMatrix);

	return allMatrix.GetMatrix();
}

void GameObject::SetLocalMatrix(float matrix[])
{
}

void GameObject::UpdateLocalMatrix()
{
	Matrix4x4 allMatrix; allMatrix.SetIdentity();
	Matrix4x4 translationMatrix; translationMatrix.SetIdentity();  translationMatrix.SetTranslate(this->GetLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.SetScale(this->GetLocalScale());
	Vector3D rotation = this->GetLocalRotation();
	Matrix4x4 xMatrix; xMatrix.SetRotationX(rotation.x);
	Matrix4x4 yMatrix; yMatrix.SetRotationY(rotation.y);
	Matrix4x4 zMatrix; zMatrix.SetRotationZ(rotation.z);

	Matrix4x4 rotMatrix; rotMatrix.SetIdentity();
	rotMatrix = rotMatrix.MultiplyTo(xMatrix.MultiplyTo(yMatrix.MultiplyTo(zMatrix)));

	allMatrix = allMatrix.MultiplyTo(scaleMatrix.MultiplyTo(rotMatrix));
	allMatrix = allMatrix.MultiplyTo(translationMatrix);
	this->localMatrix = allMatrix;
}

void GameObject::RecomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix; newMatrix.SetMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.SetScale(this->local_scale);
	Matrix4x4 transMatrix; transMatrix.SetTranslate(this->local_position);
	this->localMatrix = scaleMatrix.MultiplyTo(transMatrix.MultiplyTo(newMatrix));
	this->overrideMatrix = true;
}

void GameObject::AttachComponent(Component* component)
{
	this->componentList.push_back(component);
	component->AttachOwner(this);
}

void GameObject::DetachComponent(Component* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

Component* GameObject::FindComponentByName(String name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetName() == name) {
			return this->componentList[i];
		}
	}

	return NULL;
}

Component* GameObject::FindComponentOfType(Component::ComponentType type, String name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetName() == name && this->componentList[i]->GetType() == type) {
			return this->componentList[i];
		}
	}

	return NULL;
}

std::vector<Component*> GameObject::GetComponentsOfType(Component::ComponentType type)
{
	std::vector<Component*> foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

std::vector<Component*> GameObject::GetComponentsOfTypeRecursive(Component::ComponentType type)
{
	std::vector<Component*> foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

void GameObject::Awake()
{
}
