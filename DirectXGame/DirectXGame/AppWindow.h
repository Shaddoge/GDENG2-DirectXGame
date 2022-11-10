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
#include "Camera.h"
#include "UIManager.h"
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

	void Update(float delta_time);

	// Inherited via Window
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnResize(int width, int height) override;
	virtual void OnRMouseDown() override;
	virtual void OnRMouseUp() override;
	virtual void OnLMouseDrag(Vector2 delta_pos) override;
	virtual void OnRMouseDrag(Vector2 delta_pos) override;
	virtual void OnKeyDown(const char key) override;
	virtual void OnKeyUp(const char key) override;
private:
	SwapChain* m_swap_chain;
	VertexShader* m_vs;
	PixelShader* m_ps;
private:
	int width, height;
	TransformMode transform_mode = TransformMode::TRANSLATE;

	Camera* scene_camera;
	vector<Quad*> quads;
	vector<Cube*> cubes;
	vector<Plane*> planes;

	float delta_time = 0.0f;
	int selected_obj = 0;
};