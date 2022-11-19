#pragma once
#include <iostream>
#include "GameObject.h"
#include "Window.h"

class Plane : public GameObject
{
public:
	Plane(String name);
	void Update(float delta_time) override;
	void Draw(int width, int height) override;
	~Plane();
public:
	VertexBuffer GetVertexBuffer();
	void SetSpeed(float speed);
private:
	VertexBuffer* m_vb_outline;
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	Texture* m_tex;
private:
	float m_angle = 0.0f;
	float m_speed = 0.0f;
	float m_delta_scale = 0.0f;
};