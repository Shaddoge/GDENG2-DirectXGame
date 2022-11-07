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
#include "Matrix.h"
#include "Vector3.h"
#include "Vector2.h"

using namespace std;

class VertexShader;
class PixelShader;
class GameObject
{
public:
	GameObject(string name);
	~GameObject();

	virtual void Update(float delta_time);
	virtual void Draw(int width, int height);

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 pos);
	virtual void SetPositionMouse(Vector2 delta_pos);
	virtual void SetPositionZMouse(Vector2 delta_pos);
	Vector3 GetWorldPosition();

	void SetScale(float x, float y, float z);
	void SetScale(Vector3 scale);
	virtual void SetScaleMouse(Vector2 delta_pos);
	virtual void SetScaleZMouse(Vector2 delta_pos);
	Vector3 GetScale();

	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3 rot);
	virtual void SetRotationMouse(Vector2 delta_pos);
	virtual void SetRotationZMouse(Vector2 delta_pos);
	Vector3 GetLocalRotation();

	bool GetOutlined() { return is_outlined; };
	void SetOutlined(bool flag) { is_outlined = flag; };

	Matrix GetViewMatrix() { return view; };
	void SetViewMatrix(Matrix view_matrix) { view = view_matrix; };
private:	
	float m_angle = 0.0f;
	float m_speed = 0.0f;
	float m_delta_scale = 0.0f;
private:
	string name;
	const float transform_speed = 0.15f;
	Vector3 world_position;
	Vector3 scale;
	Vector3 local_rotation;
	bool is_outlined = false;

	Matrix view;
};

