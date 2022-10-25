#pragma once
#include <iostream>
#include "GameObject.h"
#include "EventManager.h"
#include "Window.h"

struct cube_vertex
{
	Vector3 position;
	Vector3 color;
	Vector3 color1;
};

class Cube : public GameObject, EventListener
{
public:
	Cube(string name);
	void Update(float delta_time) override;
	void Draw(int width, int height) override;
	~Cube();
public:
	VertexBuffer GetVertexBuffer();
	void SetSpeed(float speed);
	void SetViewMatrix(Matrix view);
private:
	VertexBuffer* m_vb_outline;
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
private:
	float m_angle = 0.0f;
	float m_speed = 0.0f;
	float m_delta_scale = 0.0f;

	Matrix m_view;
};