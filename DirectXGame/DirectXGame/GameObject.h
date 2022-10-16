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
	virtual void Draw(int width, int height) = 0;

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 pos);
	void SetPositionMouse(Vector2 delta_pos);
	Vector3 GetLocalPosition();

	void SetScale(float x, float y, float z);
	void SetScale(Vector3 scale);
	void SetScaleMouse(Vector2 delta_pos);
	Vector3 GetLocalScale();

	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3 rot);
	void SetRotationMouse(Vector2 delta_pos);
	Vector3 GetLocalRotation();
public:
	VertexBuffer GetVertexBuffer();
private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
private:
	string name;
	const float transform_speed = 0.15f;
	Vector3 local_position;
	Vector3 local_scale;
	Vector3 local_rotation;
};

