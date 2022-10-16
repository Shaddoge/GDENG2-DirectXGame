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

	virtual void Receive(string event_name, bool value) override;
public:
	VertexBuffer GetVertexBuffer();
private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
private:
	float m_angle = 0.0f;
	float m_time_multiplier = 1.0f;
	float m_time_tracker = 0.0f;
	const float transform_speed = 0.15f;
	float m_delta_scale = 0.0f;
};