#pragma once
#include <iostream>
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "EngineTime.h"
#include "Structs.h"
#include "Texture.h"
#include "PhysicsSystem.h"
#include "Component.h"

using namespace reactphysics3d;

class GameObjectManager;
class VertexShader;
class PixelShader;
class GameObject
{
public:
	typedef std::string String;
public:
	enum PrimitiveType {
		CAMERA,
		TEXTURED_CUBE,
		CUBE,
		PLANE,
		SPHERE,
		PHYSICS_CUBE,
		PHYSICS_PLANE,
		QUAD,
		MESH
	};

	GameObject(String name, PrimitiveType type);
	~GameObject();

	PrimitiveType GetObjectType();

	virtual void Update(float delta_time);
	virtual void Draw(int width, int height);

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3D pos);
	virtual void SetPositionMouse(Vector2D delta_pos);
	virtual void SetPositionZMouse(Vector2D delta_pos);
	Vector3D GetLocalPosition();

	void SetScale(float x, float y, float z);
	void SetScale(Vector3D local_scale);
	virtual void SetScaleMouse(Vector2D delta_pos);
	virtual void SetScaleZMouse(Vector2D delta_pos);
	Vector3D GetLocalScale();

	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3D rot);
	virtual void SetRotationMouse(Vector2D delta_pos);
	virtual void SetRotationZMouse(Vector2D delta_pos);
	Vector3D GetLocalRotation();

	String GetName();
	bool IsEnabled();
	void SetEnabled(bool flag);
	friend class GameObjectManager;

	bool GetOutlined() { return is_outlined; };
	void SetOutlined(bool flag) { is_outlined = flag; };

	Matrix4x4 GetViewMatrix() { return view; };
	void SetViewMatrix(Matrix4x4 view_matrix) { view = view_matrix; };

	float* GetPhysicsLocalMatrix();
	void SetLocalMatrix(float matrix[]);
	void UpdateLocalMatrix();
	void RecomputeMatrix(float matrix[16]);
public:
	void AttachComponent(Component* component);
	void DetachComponent(Component* component);

	Component* FindComponentByName(String name);
	Component* FindComponentOfType(Component::ComponentType type, String name);
	std::vector<Component*> GetComponentsOfType(Component::ComponentType type);
	std::vector<Component*> GetComponentsOfTypeRecursive(Component::ComponentType type);
private:	
	float m_angle = 0.0f;
	float m_speed = 0.0f;
	float m_delta_scale = 0.0f;
protected:
	String name;
	PrimitiveType objectType;
	const float transform_speed = 0.15f;
	Vector3D local_position;
	Vector3D local_scale;
	Vector3D local_rotation;
	bool is_outlined = false;	

	Matrix4x4 view;
	Matrix4x4 localMatrix;

	std::vector<Component*> componentList;
	bool overrideMatrix = false;

	virtual void Awake();
private:
	bool enabled = true;
};

