#pragma once
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "EngineTime.h"
#include "Structs.h"
#include "EventManager.h"
#include <iostream>

struct quad_vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

__declspec(align(16))
struct constant
{
	float m_angle;
};

class Quad : public EventListener
{
public:
	Quad();
	Quad(vec2 dimension, vec3 off_pos[2]);
	Quad(quad_vertex vertex_list[4]);
	void Update();
	void SetFixedTime(bool fixed);
	~Quad();

	virtual void Invoke(vec2 pos) override;
public:
	VertexBuffer GetVertexBuffer();
	void OnDrag(POINT mouse_pos);
private:
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
private:
	//unsigned long m_old_time = 0.0f;
	float m_delta_time = 0.0f;
	float m_angle = 0.0f;
	float m_time_multiplier = 1.0f;
	float m_time_tracker = 0.0f;
	bool m_add_multiplier = true;
	bool m_fixed_time = true;
	vec2 m_offset = { 0, 0 };
};

