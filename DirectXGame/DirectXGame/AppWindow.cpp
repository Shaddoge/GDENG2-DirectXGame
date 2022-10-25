#include "AppWindow.h"
#include <Windows.h>

AppWindow::AppWindow()
{

}

AppWindow::~AppWindow()
{
	
}

void AppWindow::Update(float delta_time)
{
	// Quads
	/*for (Quad* quad_ptr : quads)
	{
		quad_ptr->Update(rc);
	}*/
	scene_camera->Update(delta_time);
	// Cubes
	for (Cube* cube_ptr : cubes)
	{
		cube_ptr->SetViewMatrix(scene_camera->GetInverseWorldCam());
		cube_ptr->Update(delta_time);
		cube_ptr->Draw(width, height);
	}

	// Plane
	plane->SetViewMatrix(scene_camera->GetInverseWorldCam());
	plane->Update(delta_time);
	plane->Draw(width, height);

	m_swap_chain->Present(true);
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
	
	// Camera
	scene_camera = new Camera();
	
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
	for (int i = 0; i < 3; i++)
	{
		cube_ptr = new Cube("Cube " + to_string(i));
		Vector3 rand_position = Vector3(((rand() % 200) - 100) / 150.0f, ((rand() % 200) - 100) / 150.0f, ((rand() % 200) - 100) / 150.0f);
		cube_ptr->SetSpeed(((rand() % 200) - 100) / 50.0f);
		cube_ptr->SetPosition(rand_position);
		cubes.push_back(cube_ptr);
	}

	plane = new Plane("Plane");
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

	Update(delta_time);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();

	delete scene_camera;

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

	delete plane;

	m_swap_chain->Release();
	
	GraphicsEngine::Get()->Release();
}

void AppWindow::OnResize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void AppWindow::OnLMouseDrag(Vector2 delta_pos)
{
	if (Mouse::GetIsDown(MouseInputType::R)) return;
	delta_pos *= delta_time;
	if (selected_obj >= 0 and selected_obj <= 2)
	{
		switch (transform_mode)
		{
			case TRANSLATE: cubes[selected_obj]->SetPositionMouse(delta_pos); break;
			case SCALE: cubes[selected_obj]->SetScaleMouse(delta_pos); break;
			case ROTATE: cubes[selected_obj]->SetRotationMouse(delta_pos); break;
			default: break;
		}
	}
}

// Control camera
void AppWindow::OnRMouseDrag(Vector2 delta_pos)
{
	delta_pos *= delta_time;
	// Camera
	scene_camera->SetRotationMouse(delta_pos);

	/*
	switch (transform_mode)
	{
		case TRANSLATE: break;
		case ROTATE:  break;
		default: break;
	}

	
	if (selected_obj >= 0 and selected_obj <= 2)
	{
		switch (transform_mode)
		{
			case TRANSLATE: cubes[selected_obj]->SetPositionZMouse(delta_pos); break;
			case SCALE: cubes[selected_obj]->SetScaleZMouse(delta_pos); break;
			case ROTATE: cubes[selected_obj]->SetRotationZMouse(delta_pos); break;
			default: break;
		}
		/*switch (transform_mode)
		{
		case TRANSLATE: plane->SetPositionZMouse(delta_pos); break;
		case SCALE: plane->SetScaleZMouse(delta_pos); break;
		case ROTATE: plane->SetRotationZMouse(delta_pos); break;
		default: break;
		}
	}*/
	
}

void AppWindow::OnKeyDown(const char key)
{
	int num = key - '0';
	if (num >= 1 && num <= 3)
	{
		selected_obj = num - 1;
		
		for (Cube* cube : cubes)
		{
			cube->SetOutlined(false);
		}
		cubes[selected_obj]->SetOutlined(true);
	}
	else
	{
		if (Mouse::GetIsDown(MouseInputType::R))
		{
			switch (tolower(key))
			{
				case 'w': {
					scene_camera->SetForward(1.0f);
					break;
				}
				case 'a':  break;
				case 's': {
					scene_camera->SetForward(-1.0f);
					break;
				}
				case 'd':  break;
				default: return; break;
			}
		}
		else
		{
			switch (tolower(key))
			{
				case 'q': transform_mode = TRANSLATE; break;
				case 'w': transform_mode = SCALE; break;
				case 'e': transform_mode = ROTATE;  break;
				default: break;
			}
		}
	}
}

void AppWindow::OnKeyUp(const char key)
{
	switch (tolower(key))
	{
		case 'w': {
			scene_camera->SetForward(0.0f);
			break;
		}
		case 'a':  break;
		case 's': {
			scene_camera->SetForward(0.0f);
			break;
		}
		case 'd':  break;
		default: return; break;
	}
}
