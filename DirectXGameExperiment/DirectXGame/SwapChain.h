#pragma once
#include <d3d11.h>

class DeviceContext;
class SwapChain
{
public:
	SwapChain();
	// Initialize SwapChain for window
	bool Init(HWND hwnd, UINT width, UINT height);

	bool Present(bool vsync);

	// Release the swap chain
	bool Release();
	~SwapChain();
private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
private:
	friend class DeviceContext;
};

