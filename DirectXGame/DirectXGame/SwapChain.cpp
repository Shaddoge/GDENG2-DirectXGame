#include "SwapChain.h"
#include "GraphicsEngine.h"

SwapChain::SwapChain()
{
}

bool SwapChain::Init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::Get()->m_d3d_device;
	
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60; // 60hz
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	// Create the swap chain for the window indicated by HWND parameter
	HRESULT hr = GraphicsEngine::Get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(hr))
	{
		return false;
	}

	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		return false;
	}
	
	hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	if (FAILED(hr))
	{
		return false;
	}

	HRESULT bufferResult = this->m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	HRESULT renderResult = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();
	
	D3D11_TEXTURE2D_DESC dsTexDesc = {};
	dsTexDesc.Width = width;
	dsTexDesc.Height = height;
	dsTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsTexDesc.Usage = D3D11_USAGE_DEFAULT;
	dsTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dsTexDesc.MipLevels = 1;
	dsTexDesc.SampleDesc.Count = 1;
	dsTexDesc.SampleDesc.Quality = 0;
	dsTexDesc.ArraySize = 1;
	dsTexDesc.CPUAccessFlags = 0;
	dsTexDesc.MiscFlags = 0;

	HRESULT depthResult = device->CreateTexture2D(&dsTexDesc, NULL, &buffer);
	if (FAILED(depthResult))
	{
		return false;
	}

	// Create DSV
	HRESULT depthStencilViewResult = device->CreateDepthStencilView(buffer, NULL, &m_dsv);
	if (FAILED(depthStencilViewResult))
	{
		return false;
	}
	buffer->Release();

	// DSS
	CD3D11_DEPTH_STENCIL_DESC dssDesc;
	
	dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dssDesc.DepthFunc = D3D11_COMPARISON_LESS;
	dssDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dssDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	dssDesc.DepthEnable = false;
	dssDesc.StencilEnable = true;

	dssDesc.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;
	dssDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dssDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dssDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dssDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dssDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dssDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dssDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR_SAT;

	dssDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
	
	// Create DSS
	HRESULT depthStencilStateResult = device->CreateDepthStencilState(&dssDesc, &m_dss);
	buffer->Release();

	if (FAILED(depthStencilStateResult))
	{
		return false;
	}

	return true;
}

bool SwapChain::Present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);

	return true;
}

bool SwapChain::Release()
{
	m_swap_chain->Release();
	delete this;
	return true;
}

SwapChain::~SwapChain()
{
}
