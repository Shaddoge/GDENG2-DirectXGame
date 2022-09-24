#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

AppWindow::AppWindow()
{

}

AppWindow::~AppWindow()
{

}

void AppWindow::OnCreate()
{
	Window::OnCreate();
	GraphicsEngine::Get()->Init();
	m_swap_chain = GraphicsEngine::Get()->CreateSwapChain();

	RECT rc = this->GetClientWindowRect();
	m_swap_chain->Init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex rectangle_0[] = {
		// X - Y - Z				Color
		{-0.75f,-0.125f, 0.0f,		1,0,0},
		{-0.75f, 0.125f, 0.0f,		0,1,0},
		{-0.25f,-0.125f, 0.0f,		0,0,1},
		{-0.25f, 0.125f, 0.0f,		1,1,0}
	};

	vertex triangle_0[] = {
		// X - Y - Z				Color
		{-0.1f,-0.075f, 0.0f,		1,0,0},
		{ 0.0f, 0.075f, 0.0f,		0,0,1},
		{ 0.1f,-0.075f, 0.0f,		0,1,0}, 
		
	};

	vertex rectangle_1[] = {
		// X - Y - Z				Color
		{0.25f,-0.125f, 0.0f,		0,1,0},
		{0.25f, 0.125f, 0.0f,		0,1,0},
		{0.75f,-0.125f, 0.0f,		0,1,0},
		{0.75f, 0.125f, 0.0f,		0,1,0}
	};

	m_vb_0 = GraphicsEngine::Get()->CreateVertexBuffer();
	m_vb_1 = GraphicsEngine::Get()->CreateVertexBuffer();
	m_vb_2 = GraphicsEngine::Get()->CreateVertexBuffer();

	UINT size_list_0 = ARRAYSIZE(rectangle_0);
	UINT size_list_1 = ARRAYSIZE(triangle_0);
	UINT size_list_2 = ARRAYSIZE(rectangle_1);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb_0->Load(rectangle_0, sizeof(vertex), size_list_0, shader_byte_code, size_shader);
	m_vb_1->Load(triangle_0, sizeof(vertex), size_list_1, shader_byte_code, size_shader);
	m_vb_2->Load(rectangle_1, sizeof(vertex), size_list_2, shader_byte_code, size_shader);
	GraphicsEngine::Get()->ReleaseCompiledShader();

	// Pixel Shader
	GraphicsEngine::Get()->CompilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::Get()->CreatePixelShader(shader_byte_code, size_shader);
	GraphicsEngine::Get()->ReleaseCompiledShader(); 

}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	// Clear render target
	GraphicsEngine::Get()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	// Set viewport of render
	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	// Set default shader in graphics pipeline
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexShader(m_vs);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetPixelShader(m_ps);

	// Object 0
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb_0);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawTriangleStrip(m_vb_0->GetSizeVertexList(), 0);
	
	// Object 1
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb_1);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawTriangleStrip(m_vb_1->GetSizeVertexList(), 0);

	// Object 2
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb_2);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawTriangleStrip(m_vb_2->GetSizeVertexList(), 0);

	m_swap_chain->Present(true);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	m_vb_0->Release();
	m_vb_1->Release();
	m_vb_2->Release();
	m_swap_chain->Release();
	m_vs->Release();
	m_ps->Release();
	GraphicsEngine::Get()->Release();
}
