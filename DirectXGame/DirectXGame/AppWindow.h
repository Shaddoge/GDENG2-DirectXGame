#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;
private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb_0;
	VertexBuffer* m_vb_1;
	VertexBuffer* m_vb_2;
	VertexShader* m_vs;
	PixelShader* m_ps;
};

