#pragma once
#include <iostream>
#include "GameObject.h"
#include "EventManager.h"
#include "Window.h"

struct quad_vertex
{
	Vector3 position;
	Vector3 color;
	Vector3 color1;
};

class Quad : public GameObject
{
public:
	Quad(string name);
	Quad(string name, Vector3 position);
	Quad(string name, Vector2 dimension);
	Quad(string name, quad_vertex vertex_list[4]);
	void Update(float delta_time) override;
	void Draw(int width, int height) override;
	~Quad();
public:
	VertexBuffer GetVertexBuffer();
	void SetSpeed(float speed);
private:
	VertexBuffer* m_vb_outline;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
private:
	float m_angle = 0.0f;
	float m_speed = 0.0f;
	float m_delta_scale = 0.0f;
};