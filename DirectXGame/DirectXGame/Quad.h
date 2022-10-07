#pragma once
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "EngineTime.h"

struct vec2
{
	float x, y;
};

struct vec3
{
	float x, y, z;
};

struct vertex
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

class Quad
{
public:
	Quad();
	Quad(vec2 dimension, vec3 off_pos[2]);
	Quad(vertex vertex_list[4]);
	
	void Update();
	~Quad();
public:
	VertexBuffer GetVertexBuffer();
private:
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
private:
	unsigned long m_old_time = 0.0f;
	float m_delta_time = 0.0f;
	float m_angle = 0.0f;
	float m_time_multiplier = 1.0f;
	bool m_add_multiplier = true;
	float m_time_tracker = 0.0f;
};

