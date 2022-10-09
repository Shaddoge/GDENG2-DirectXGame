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
	
	quad_vertex quad_vertices[4] = {
		{Vector3(-0.75,-0.8, 0.0),	Vector3(-0.3, 0.0, 0.0),	Vector3(0.1, 0.0, 0.0),  Vector3(0,1,0)},
		{Vector3(-0.9,  0.2, 0.0),	Vector3(-0.1, 0.8, 0.0),	Vector3(1.0, 0.9, 0.0),  Vector3(1,1,0)},
		{Vector3(0.1, -0.25, 0.0),	Vector3(0.8, -0.6, 0.0),	Vector3(0.0, 0.0, 1.0),  Vector3(1,0,0)},
		{Vector3(0.05, 0.21, 0.0),	Vector3(0.9,  0.8, 0.0),	Vector3(1.0, 1.0, 1.0),  Vector3(0,0,1)}
	};

	// Quads
	Quad* quad_ptr;
	for (int i = 0; i < 3; i++)
	{
		Vector2 vec = Vector2(-0.6 + (i * 0.6), -0.6 + (i * 0.6)); // Offset
		quad_ptr = new Quad(vec);
		quads.push_back(quad_ptr);
		//EventManager::BindListener("MouseLDown", quad_ptr);
	}
}
void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	// Clear render target
	GraphicsEngine::Get()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	// Set viewport of render
	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	// Quads
	for (Quad* quad_ptr : quads)
	{
		quad_ptr->Update(rc);
	}

	m_swap_chain->Present(true);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	for (Quad* quad_ptr : quads)
	{
		delete quad_ptr;
	}
	quads.clear();

	m_swap_chain->Release();
	
	GraphicsEngine::Get()->Release();
}

void AppWindow::OnMouseDrag(const Vector2 delta_pos)
{
	switch (transform_mode)
	{
		case TRANSLATE: quads[selected_quad]->Translate(delta_pos); break;
		case SCALE: quads[selected_quad]->Scale(delta_pos); break;
		default: break;
	}
}

void AppWindow::OnKeyDown(const char key)
{
	int num = key - '0';
	if (num >= 1 && num <= 3)
	{
		selected_quad = num - 1;
	}
	else
	{
		switch (tolower(key))
		{
		case 'q': transform_mode = TRANSLATE; return; break;
		case 'w': transform_mode = SCALE; return; break;
		default: break;
		}
	}
}
