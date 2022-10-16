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

	// Quads
	/*Quad* quad_ptr;
	for (int i = 0; i < 3; i++)
	{
		Vector2 vec = Vector2(-0.6 + (i * 0.6), -0.6 + (i * 0.6)); // Offset
		quad_ptr = new Quad(vec);
		quads.push_back(quad_ptr);
		//EventManager::BindListener("MouseLDown", quad_ptr);
	}*/

	// Cubes
	Cube* cube_ptr;
	for (int i = 0; i < 1; i++)
	{
		//Vector3 vec = Vector3(-0.6 + (i * 0.6), -0.6 + (i * 0.6), -0.6 + (i * 0.6)); // Offset
		cube_ptr = new Cube("Cube " + to_string(i));
		cubes.push_back(cube_ptr);
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
	
	delta_time = EngineTime::GetDeltaTime();

	// Quads
	/*for (Quad* quad_ptr : quads)
	{
		quad_ptr->Update(rc);
	}*/

	// Cubes
	for (Cube* cube_ptr : cubes)
	{
		cube_ptr->Update(delta_time);
		cube_ptr->Draw(width, height);
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

	for (Cube* cube_ptr : cubes)
	{
		delete cube_ptr;
	}
	cubes.clear();

	m_swap_chain->Release();
	
	GraphicsEngine::Get()->Release();
}

void AppWindow::OnResize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void AppWindow::OnMouseDrag(Vector2 delta_pos)
{
	delta_pos *= delta_time;
	switch (transform_mode)
	{
		case TRANSLATE: cubes[selected_quad]->SetPositionMouse(delta_pos); break;
		case SCALE: cubes[selected_quad]->SetScaleMouse(delta_pos); break;
		case ROTATE: cubes[selected_quad]->SetRotationMouse(delta_pos); break;
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
		case 'e': transform_mode = ROTATE; return; break;
		default: break;
		}
	}
}
