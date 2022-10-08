#include "AppWindow.h"
#include <Windows.h>


AppWindow::AppWindow()
{

}

AppWindow::~AppWindow()
{
	
}

void AppWindow::OnCreate()
{
	Mouse::Initialize();
	EngineTime::Initialize();
	EventManager::Initialize();
	
	Window::OnCreate();
	GraphicsEngine::Get()->Init();
	m_swap_chain = GraphicsEngine::Get()->CreateSwapChain();
	
	RECT rc = this->GetClientWindowRect();
	m_swap_chain->Init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	
	// Slide 13
	quad_vertex quad_vertices[4] = {
		{-0.75,-0.8,  0.0,	-0.3, 0.0, 0.0,  0.1, 0.0, 0.0,  0,1,0},
		{-0.9,  0.2,  0.0,	-0.1, 0.8, 0.0,  1.0, 0.9, 0.0,  1,1,0},
		{ 0.1, -0.25, 0.0,	 0.8,-0.6, 0.0,  0.0, 0.0, 1.0,  1,0,0},
		{ 0.05, 0.21, 0.0,	 0.9, 0.8, 0.0,  1.0, 1.0, 1.0,  0,0,1}
	};

	// Slide 14
	/*vertex quad_vertices[4] = {
		{-0.7, -0.9,  0.0,	-0.3, 0.0, 0.0,  0.1, 0.0, 0.0,  0,1,0},
		{-0.9,  0.2,  0.0,	-0.1, 0.8, 0.0,  1.0, 0.9, 0.0,  1,1,0},
		{ 1.0, -0.2, 0.0,	 0.0,-0.6, 0.0,  0.0, 0.0, 2.0,  1,0,0},
		{-0.7, -0.9, 0.0,	 0.9, 0.78,0.0,  1.0, 1.0, 1.0,  0,0,1}
	};*/
	
	quad = new Quad(quad_vertices);
	// For Slide 13
	quad->SetFixedTime(false);
	// Quad with dimension
	/*vec2 quad_dimension = {1, 0.5f};
	vec3 quad_off[2] = {{0,0,0}, {0.3,0.3,0}};
	quad = new Quad(quad_dimension, quad_off);*/

	// Quads
	/*Quad* quad_ptr;
	for (int i = 0; i < 3; i++)
	{
		vec3 vec = { -0.6 + (i * 0.6), -0.6 + (i * 0.6), 0}; // Offset
		quad_ptr = new Quad(vec, vec);
		quads[i] = quad_ptr;
	}*/
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	// Clear render target
	GraphicsEngine::Get()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	// Set viewport of render
	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	POINT mouse_pos;
	::GetCursorPos(&mouse_pos);

	quad->Update();
	// Quads
	/*for (int i = 0; i < 3; i++)
	{
		quads[i]->Update();
	}*/

	m_swap_chain->Present(true);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	delete quad;
	// Quads
	/*for (int i = 2; i >= 0; i--)
	{
		delete quads[i];
	}*/
	m_swap_chain->Release();
	
	GraphicsEngine::Get()->Release();
}
