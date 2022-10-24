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
	ID3D11DepthStencilView* m_dsv;
	ID3D11DepthStencilState* m_dss;
private:
	friend class DeviceContext;
};

