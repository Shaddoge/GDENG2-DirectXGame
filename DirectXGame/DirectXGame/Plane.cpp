#include "Plane.h"

Plane::Plane(string name) : GameObject(name)
{
	plane_vertex vertex_list[8] = {
		// X - Y - Z						Color
		// Front Face
		{Vector3(-0.5f,-0.0f, -0.5f),	Vector3(1,1,1),		Vector3(1,1,1)},
		{Vector3(-0.5f, 0.0f, -0.5f),	Vector3(1,1,1),		Vector3(1,1,1)},
		{Vector3( 0.5f, 0.0f, -0.5f),	Vector3(1,1,1),		Vector3(1,1,1)},
		{Vector3( 0.5f,-0.0f, -0.5f),	Vector3(1,1,1),		Vector3(1,1,1)},

		// Back Face
		{Vector3( 0.5f,-0.0f, 0.5f),	Vector3(1,1,1),		Vector3(1,1,1)},
		{Vector3( 0.5f, 0.0f, 0.5f),	Vector3(1,1,1),		Vector3(1,1,1)},
		{Vector3(-0.5f, 0.0f, 0.5f),	Vector3(1,1,1),		Vector3(1,1,1)},
		{Vector3(-0.5f,-0.0f, 0.5f),	Vector3(1,1,1),		Vector3(1,1,1)}
	};

	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_vertex_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] = {
		// Front
		//0,1,2,
		//2,3,0,
		// Back
		//4,5,6,
		//6,7,4,
		// Top
		1,6,5,
		5,2,1,
		// Bottom
		7,0,3,
		3,4,7,
		// Right
		//3,2,5,
		//5,4,3,
		// Left
		//7,6,1,
		//1,0,7
	};

	m_ib = GraphicsEngine::Get()->CreateIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->Load(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(&vertex_list, sizeof(plane_vertex), size_vertex_list, shader_byte_code, size_shader);

	// Pixel Shader
	GraphicsEngine::Get()->CompilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::Get()->CreatePixelShader(shader_byte_code, size_shader);
	GraphicsEngine::Get()->ReleaseCompiledShader();

	// Constant Buffer
	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::Get()->CreateConstantBuffer();
	m_cb->Load(&cc, sizeof(constant));
}

void Plane::Update(float delta_time)
{
	m_angle += 1.57f * delta_time;
	m_delta_scale += delta_time * m_speed;
}

void Plane::Draw(int width, int height)
{
	constant cc;

	Vector3 local_scale = GetLocalScale();
	// Scale
	cc.m_world.SetScale(Vector3(local_scale.x, local_scale.y, local_scale.z));

	Vector3 local_rotation = GetLocalRotation();
	// Temp Matrix
	Matrix temp;
	// Rotation Z
	temp.SetIdentity();
	temp.SetRotationZ(local_rotation.z);
	cc.m_world *= temp;
	// Rotation Y
	temp.SetIdentity();
	temp.SetRotationY(local_rotation.y);
	cc.m_world *= temp;
	// Rotation X
	temp.SetIdentity();
	temp.SetRotationX(local_rotation.x);
	cc.m_world *= temp;

	Vector3 local_pos = GetLocalPosition();
	// Translate
	temp.SetTranslate(Vector3(local_pos.x, local_pos.y, local_pos.z));
	cc.m_world *= temp;

	cc.m_view.SetIdentity();
	cc.m_projection.SetOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	cc.m_angle = m_angle;

	m_cb->Update(GraphicsEngine::Get()->GetImmediateDeviceContext(), &cc);

	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetConstantBuffer(m_vs, m_cb);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetConstantBuffer(m_ps, m_cb);

	// Set default shader in graphics pipeline
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexShader(m_vs);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetPixelShader(m_ps);

	// Set Vertex Buffer
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);
	// Set Index Buffer
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetIndexBuffer(m_ib);

	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawIndexedTriangleList(m_ib->GetSizeIndexList(), 0, 0);
}

Plane::~Plane()
{
	EventManager::UnbindListener("MouseMove", this);
	m_vb->Release();
	m_ib->Release();
	m_cb->Release();
	m_vs->Release();
	m_ps->Release();
}

VertexBuffer Plane::GetVertexBuffer()
{
	return *m_vb;
}

void Plane::SetSpeed(float speed)
{
	this->m_speed = speed;
}