#include "Quad.h"

Quad::Quad()
{
	//EventManager::BindEvent("MouseMove", this);
	quad_vertex vertex_list[4] = {
		// X - Y - Z										Color
		{Vector3(-0.25f,-0.25f, 0.0f),		Vector3(-0.25f,-0.25f, 0.0f),		Vector3(1,0,0),	Vector3(0,0,1)},
		{Vector3(-0.25f, 0.25f, 0.0f),		Vector3(-0.25f, 0.25f, 0.0f),		Vector3(0,1,0),	Vector3(0,1,1)},
		{Vector3(0.25f,-0.25f, 0.0f),		Vector3(0.25f, -0.25f, 0.0f),		Vector3(0,0,1),	Vector3(1,0,0)},
		{Vector3(0.25f, 0.25f, 0.0f),		Vector3(0.25f,  0.25f, 0.0f),		Vector3(0,0,0),	Vector3(1,1,1)}
	};

	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(&vertex_list, sizeof(quad_vertex), size_list, shader_byte_code, size_shader);

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

Quad::Quad(Vector2 position)
{
	m_position = position;
	quad_vertex vertex_list[4] = {
		// X - Y - Z										Color
		{Vector3(-0.25f,-0.25f, 0.0f),		Vector3(-0.25f,-0.25f, 0.0f),		Vector3(1,0,0),	Vector3(0,0,1)},
		{Vector3(-0.25f, 0.25f, 0.0f),		Vector3(-0.25f, 0.25f, 0.0f),		Vector3(0,1,0),	Vector3(0,1,1)},
		{Vector3(0.25f,-0.25f, 0.0f),		Vector3(0.25f, -0.25f, 0.0f),		Vector3(0,0,1),	Vector3(1,0,0)},
		{Vector3(0.25f, 0.25f, 0.0f),		Vector3(0.25f,  0.25f, 0.0f),		Vector3(0,0,0),	Vector3(1,1,1)}
	};

	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(&vertex_list, sizeof(quad_vertex), size_list, shader_byte_code, size_shader);

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

// With offset positioning
Quad::Quad(Vector2 dimension, Vector3 off_pos[2])
{
	//EventManager::BindEvent("MouseMove", this);
	float x_half = dimension.x / 2;
	float y_half = dimension.y / 2;
	quad_vertex vertex_list[4] = {
		
		// X - Y - Z																											Color
		{Vector3(-x_half + off_pos[0].x,-y_half + off_pos[0].y, 0.0f),		Vector3(-x_half + off_pos[1].x,-y_half + off_pos[1].y, 0.0f),		Vector3(1,0,0),	Vector3(0,0,1)},
		{Vector3(-x_half + off_pos[0].x, y_half + off_pos[0].y, 0.0f),		Vector3(-x_half + off_pos[1].x, y_half + off_pos[1].y, 0.0f),		Vector3(0,1,0),	Vector3(0,1,1)},
		{Vector3(x_half + off_pos[0].x,-y_half + off_pos[0].y, 0.0f),		Vector3(x_half + off_pos[1].x,-y_half + off_pos[1].y, 0.0f),		Vector3(0,0,1),	Vector3(1,0,0)},
		{Vector3(x_half + off_pos[0].x, y_half + off_pos[0].y, 0.0f),		Vector3(x_half + off_pos[1].x, y_half + off_pos[1].y, 0.0f),		Vector3(0,0,0),	Vector3(1,1,1)}
	};
	
	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(&vertex_list, sizeof(quad_vertex), size_list, shader_byte_code, size_shader);

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

Quad::Quad(quad_vertex vertex_list[4])
{
	//EventManager::BindEvent("MouseMove", this);
	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_list = 4;

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(vertex_list, sizeof(quad_vertex), size_list, shader_byte_code, size_shader);

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

void Quad::Update(RECT rc)
{
	m_delta_time = EngineTime::GetDeltaTime();
	if (m_fixed_time)
		m_angle += 1.57f * m_delta_time;
	else
	{
		float multiplied_time = m_delta_time * m_time_multiplier;
		m_time_multiplier = abs(sinf(m_time_tracker)) * 8;
		m_time_tracker += m_delta_time * 0.2f;

		m_angle += 1.57f * multiplied_time;
	}

	constant cc;
	cc.m_world.SetScale(Vector3(m_scale.x, m_scale.y, 0.0f));
	Matrix mat_translate;
	mat_translate.SetTranslate(Vector3(m_position.x, m_position.y, 0));

	cc.m_world *= mat_translate;
	cc.m_view.SetIdentity();
	cc.m_projection.SetOrthoLH((rc.right - rc.left) / 400.0f, (rc.bottom - rc.top) / 400.0f, -4.0f, 4.0f);
	cc.m_angle = m_angle;

	m_cb->Update(GraphicsEngine::Get()->GetImmediateDeviceContext(), &cc);

	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetConstantBuffer(m_vs, m_cb);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetConstantBuffer(m_ps, m_cb);

	// Set default shader in graphics pipeline
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexShader(m_vs);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetPixelShader(m_ps);

	// Object 0
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawTriangleStrip(m_vb->GetSizeVertexList(), 0);
}

void Quad::SetFixedTime(bool fixed)
{
	this->m_fixed_time = fixed;
}

Quad::~Quad()
{
	EventManager::UnbindListener("MouseMove", this);
	m_vb->Release();
	m_vs->Release();
	m_ps->Release();
}

void Quad::Receive(string event_name, bool value)
{
	if (event_name != "MouseLDown") return;
	
	cout << "Mouse L Down: " << value << endl;
}

void Quad::Receive(string event_name, Vector2 pos)
{
	if (event_name != "MouseMove") return;

	Translate(pos);
}

VertexBuffer Quad::GetVertexBuffer()
{
	return *m_vb;
}

void Quad::Translate(Vector2 delta_pos)
{
	m_position += Vector2(m_delta_time * delta_pos.x * transform_speed, m_delta_time* delta_pos.y * transform_speed);
}

void Quad::Scale(Vector2 delta_pos)
{
	m_scale += Vector2(m_delta_time * delta_pos.x * transform_speed, m_delta_time * delta_pos.y * transform_speed);
}