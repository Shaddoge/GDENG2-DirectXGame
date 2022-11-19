#pragma once
#include "GameObject.h"

class MeshObj : public GameObject
{
public:
	MeshObj(String name, int mesh_type);
	void Update(float delta_time) override;
	void Draw(int width, int height) override;
	~MeshObj();
private:
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	Texture* m_tex;
	Mesh* m_mesh;
private:
	float m_angle = 0.0f;
	float m_speed = 0.0f;
	float m_delta_scale = 0.0f;
};

