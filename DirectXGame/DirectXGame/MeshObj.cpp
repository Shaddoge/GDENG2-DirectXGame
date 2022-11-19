#include "MeshObj.h"
#include "Mesh.h"

MeshObj::MeshObj(String name, int mesh_type) : GameObject(name, GameObject::PrimitiveType::MESH)
{
    m_tex = GraphicsEngine::Get()->GetTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick.png");
    
	switch (mesh_type)
	{
	case 0: m_mesh = GraphicsEngine::Get()->GetMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\teapot.obj"); break;
	case 1: m_mesh = GraphicsEngine::Get()->GetMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\armadillo.obj"); break;
	case 2: m_mesh = GraphicsEngine::Get()->GetMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\bunny.obj"); break;
	default: m_mesh = GraphicsEngine::Get()->GetMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\teapot.obj"); break;
	}
	
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);

	// Pixel Shader
	GraphicsEngine::Get()->CompilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::Get()->CreatePixelShader(shader_byte_code, size_shader);
	GraphicsEngine::Get()->ReleaseCompiledShader();
	
	// Constant Buffer
	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::Get()->CreateConstantBuffer();
	m_cb->Load(&cc, sizeof(constant));
}

void MeshObj::Update(float delta_time)
{
}

void MeshObj::Draw(int width, int height)
{
	constant cc;

	Vector3D local_scale = GetLocalScale();
	// Scale
	cc.m_world.SetIdentity();
	cc.m_world.SetScale(Vector3D(local_scale.x, local_scale.y, local_scale.z));

	Vector3D local_rotation = GetLocalRotation();
	// Temp Matrix4x4
	Matrix4x4 temp;
	// Rotation Z
	temp.SetIdentity();
	temp.SetRotationZ(local_rotation.z);
	cc.m_world *= temp;
	// Rotation Y
	temp.SetIdentity();
	temp.SetRotationY(local_rotation.y);
	cc.m_world *= temp;
	// Rotation X
	temp.SetIdentity();
	temp.SetRotationX(local_rotation.x);
	cc.m_world *= temp;

	Vector3D world_pos = GetLocalPosition();
	// Translate
	temp.SetIdentity();
	temp.SetTranslate(Vector3D(world_pos.x, world_pos.y, world_pos.z));

	cc.m_world *= temp;

	cc.m_view.SetIdentity();
	cc.m_view = GetViewMatrix();
	//cc.m_projection.SetOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	cc.m_projection.SetPerspectiveFovLH(1.57f, (float)width / (float)height, 0.05f, 100.0f);
	cc.m_angle = m_angle;

	m_cb->Update(GraphicsEngine::Get()->GetImmediateDeviceContext(), &cc);

	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetConstantBuffer(m_vs, m_cb);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetConstantBuffer(m_ps, m_cb);

	// Set default shader in graphics pipeline
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexShader(m_vs);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetPixelShader(m_ps);

	if (m_tex != nullptr)
		GraphicsEngine::Get()->GetImmediateDeviceContext()->SetTexture(m_ps, m_tex);

	// Set Buffers
	if (m_mesh != nullptr)
	{
		GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_mesh->GetVertexBuffer());
		GraphicsEngine::Get()->GetImmediateDeviceContext()->SetIndexBuffer(m_mesh->GetIndexBuffer());

		GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawIndexedTriangleList(m_mesh->GetIndexBuffer()->GetSizeIndexList(), 0, 0);
	}
}

MeshObj::~MeshObj()
{
	m_cb->Release();
	m_vs->Release();
	m_ps->Release();
}
