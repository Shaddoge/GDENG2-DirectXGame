#pragma once
#include <iostream>
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "EngineTime.h"
#include "Structs.h"
#include "EventManager.h"
#include "Matrix.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Window.h"

struct quad_vertex
{
	Vector3 position;
	Vector3 position1;
	Vector3 color;
	Vector3 color1;
};

class Quad : public EventListener
{
public:
	Quad();
	Quad(Vector2 position);
	Quad(Vector2 dimension, Vector3 off_pos[2]);
	Quad(quad_vertex vertex_list[4]);
	void Update(RECT rc);
	void SetFixedTime(bool fixed);
	~Quad();

	virtual void Receive(string event_name, bool value);
	virtual void Receive(string event_name, Vector2 pos) override;
public:
	VertexBuffer GetVertexBuffer();
	void Translate(Vector2 delta_pos);
	void Scale(Vector2 delta_pos);
private:
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
private:
	float m_delta_time = 0.0f;
	float m_angle = 0.0f;
	float m_time_multiplier = 1.0f;
	float m_time_tracker = 0.0f;
	bool m_fixed_time = true;
	const float transform_speed = 0.15f;
	Vector2 m_position = Vector2();
	Vector2 m_scale = Vector2(1.0f, 1.0f);
};