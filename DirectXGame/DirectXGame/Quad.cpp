#include "Quad.h"

Quad::Quad()
{
	EventManager::BindEvent("Mouse", this);
	quad_vertex vertex_list[4] = {
		// X - Y - Z										Color
		{-0.25f,-0.25f, 0.0f,		-0.25f,-0.25f, 0.0f,		1,0,0,	0,0,1},
		{-0.25f, 0.25f, 0.0f,		-0.25f, 0.25f, 0.0f,		0,1,0,	0,1,1},
		{ 0.25f,-0.25f, 0.0f,		 0.25f,-0.25f, 0.0f,		0,0,1,	1,0,0},
		{ 0.25f, 0.25f, 0.0f,		 0.25f, 0.25f, 0.0f,		0,0,0,	1,1,1}
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
Quad::Quad(vec2 dimension, vec3 off_pos[2])
{
	EventManager::BindEvent("Mouse", this);
	float x_half = dimension.x / 2;
	float y_half = dimension.y / 2;
	quad_vertex vertex_list[4] = {
		
		// X - Y - Z																											Color
		{-x_half + off_pos[0].x,-y_half + off_pos[0].y, 0.0f,		-x_half + off_pos[1].x,-y_half + off_pos[1].y, 0.0f,		1,0,0,	0,0,1},
		{-x_half + off_pos[0].x, y_half + off_pos[0].y, 0.0f,		-x_half + off_pos[1].x, y_half + off_pos[1].y, 0.0f,		0,1,0,	0,1,1},
		{ x_half + off_pos[0].x,-y_half + off_pos[0].y, 0.0f,		 x_half + off_pos[1].x,-y_half + off_pos[1].y, 0.0f,		0,0,1,	1,0,0},
		{ x_half + off_pos[0].x, y_half + off_pos[0].y, 0.0f,		 x_half + off_pos[1].x, y_half + off_pos[1].y, 0.0f,		0,0,0,	1,1,1}
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
	EventManager::BindEvent("Mouse", this);
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

void Quad::Update()
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

	/*unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	if (m_add_multiplier == true)
	{
		m_time_multiplier += m_delta_time;
		if (m_time_multiplier >= 10.0f)
		{
			m_add_multiplier = false;
		}
	}
	else
	{
		m_time_multiplier -= m_delta_time;
		if (m_time_multiplier <= 1.0f)
		{
			m_add_multiplier = true;
		}
	}*/
		
	constant cc;
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
	EventManager::UnbindEvent("Mouse", this);
	m_vb->Release();
	m_vs->Release();
	m_ps->Release();
}

void Quad::Invoke(vec2 pos)
{
	cout << pos.x << "," << pos.y << endl;
	POINT point_pos = { pos.x, pos.y };
	OnDrag(point_pos);
}

VertexBuffer Quad::GetVertexBuffer()
{
	return *m_vb;
}

void Quad::OnDrag(POINT mouse_pos)
{
	m_offset = { m_delta_time * mouse_pos.x, m_delta_time * mouse_pos.y };
	std::cout << m_offset.x << "," << m_offset.y << std::endl;
	//std::cout << "Drag!" << std::endl;
}