#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include <d3dcompiler.h>
#include <iostream>

GraphicsEngine::GraphicsEngine()
{
    try
    {
        m_tex_manager = new TextureManager();
    }
    catch (...) { throw std::exception("Texture Manager not created successfully"); }

    try
    {
        m_mesh_manager = new MeshManager();
    }
    catch (...) { throw std::exception("Mesh Manager not created successfully"); }

    void* shader_byte_code = nullptr;
    size_t size_shader = 0;

    // Vertex Shader
    CompileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
    ::memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
    m_mesh_layout_size = size_shader;
    ReleaseCompiledShader();
}

bool GraphicsEngine::Init()
{
    D3D_DRIVER_TYPE driver_types[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };
    UINT num_driver_types = ARRAYSIZE(driver_types);

    D3D_FEATURE_LEVEL feature_levels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };
    UINT num_feature_levels = ARRAYSIZE(feature_levels);

    HRESULT res = 0;

    for (UINT i = 0; i < num_driver_types; i++)
    {
        res = D3D11CreateDevice(NULL, driver_types[i], NULL, NULL, feature_levels, num_feature_levels,
            D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);

        if (SUCCEEDED(res))
        {
            break;
        }
    }

    if (FAILED(res))
    {
        return false;
    }

    m_imm_device_context = new DeviceContext(m_imm_context);

    m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void **)&m_dxgi_device);
    m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void **)&m_dxgi_adapter);
    m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void **)&m_dxgi_factory);

    return true;
}

bool GraphicsEngine::Release()
{
    if (m_vs)m_vs->Release();
    if (m_ps)m_ps->Release();

    if (m_vsblob)m_vsblob->Release();
    if (m_psblob)m_psblob->Release();
        
    m_dxgi_device->Release();
    m_dxgi_adapter->Release();
    m_dxgi_factory->Release();

    m_imm_device_context->Release();
    m_d3d_device->Release();

    return true;
}

GraphicsEngine::~GraphicsEngine()
{
    delete m_tex_manager;
    delete m_mesh_manager;
}

SwapChain* GraphicsEngine::CreateSwapChain()
{
    return new SwapChain();
}

DeviceContext* GraphicsEngine::GetImmediateDeviceContext()
{
    return this->m_imm_device_context;
}

ID3D11Device* GraphicsEngine::GetDirectXDevice()
{
    return this->m_d3d_device;
}

VertexBuffer* GraphicsEngine::CreateVertexBuffer()
{
    return new VertexBuffer();
}

VertexBuffer* GraphicsEngine::CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list,
    void* shader_byte_code, UINT size_byte_shader)
{

    VertexBuffer* vb = nullptr;
    try
    {
        vb = new VertexBuffer(list_vertices, size_vertex, size_list, shader_byte_code, size_byte_shader);
    }
    catch (...) {}
    return vb;
}

IndexBuffer* GraphicsEngine::CreateIndexBuffer()
{
    return new IndexBuffer();
}

IndexBuffer* GraphicsEngine::CreateIndexBuffer(void* list_indices, UINT size_list)
{
    IndexBuffer* ib = nullptr;
    try
    {
        ib = new IndexBuffer(list_indices, size_list);
    }
    catch (...) {}
    return ib;
}

ConstantBuffer* GraphicsEngine::CreateConstantBuffer()
{
    return new ConstantBuffer();
}

VertexShader* GraphicsEngine::CreateVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
    VertexShader* vs = new VertexShader();
    if (!vs->Init(shader_byte_code, byte_code_size))
    {
        vs->Release();
        return nullptr;
    }

    return vs;
}

PixelShader* GraphicsEngine::CreatePixelShader(const void* shader_byte_code, size_t byte_code_size)
{
    PixelShader* ps = new PixelShader();
    
    if (!ps->Init(shader_byte_code, byte_code_size))
    {
        ps->Release();
        return nullptr;
    }

    return ps;
}

bool GraphicsEngine::CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
    ID3DBlob* error_blob = nullptr;
    if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
    {
        
        if (error_blob) error_blob->Release();
        return false;
    }

    *shader_byte_code = m_blob->GetBufferPointer();
    *byte_code_size = m_blob->GetBufferSize();  

    return true;
}

bool GraphicsEngine::CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
    ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void GraphicsEngine::ReleaseCompiledShader()
{
    if (m_blob) m_blob->Release();
}

TextureManager* GraphicsEngine::GetTextureManager()
{
    return m_tex_manager;
}

MeshManager* GraphicsEngine::GetMeshManager()
{
    return m_mesh_manager;
}

void GraphicsEngine::GetVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
    *byte_code = m_mesh_layout_byte_code;
    *size = m_mesh_layout_size;
}

GraphicsEngine* GraphicsEngine::Get()
{
    static GraphicsEngine engine;
    return &engine;
}
