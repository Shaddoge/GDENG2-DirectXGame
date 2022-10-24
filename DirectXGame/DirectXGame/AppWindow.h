#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "EngineTime.h"
#include "Mouse.h"
#include "Quad.h"
#include "Cube.h"
#include "Plane.h"
#include "EventManager.h"
#include <vector>

enum TransformMode
{
	TRANSLATE,
	SCALE,
	ROTATE
};

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnResize(int width, int height) override;
	virtual void OnLMouseDrag(Vector2 delta_pos) override;
	virtual void OnRMouseDrag(Vector2 delta_pos) override;
	virtual void OnKeyDown(const char key) override;
private:
	SwapChain* m_swap_chain;
	VertexShader* m_vs;
	PixelShader* m_ps;
private:
	int width, height;
	TransformMode transform_mode = TransformMode::TRANSLATE;
	vector<Quad*> quads;
	vector<Cube*> cubes;
	Plane* plane;
	float delta_time = 0.0f;
	int selected_obj = 0;
};