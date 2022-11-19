#include "Plane.h"

Plane::Plane(String name) : GameObject(name, GameObject::PrimitiveType::PLANE)
{
	m_tex = GraphicsEngine::Get()->GetTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\wood.jpg");
	float plane_size = 1.0f;
	std::cout << (m_tex == nullptr) << std::endl;
	Vector3D position_list[] =
	{
		{Vector3D(-plane_size / 2,-0.0f, -plane_size / 2)},
		{Vector3D(-plane_size / 2, 0.0f, -plane_size / 2)},
		{Vector3D( plane_size / 2, 0.0f, -plane_size / 2)},
		{Vector3D( plane_size / 2,-0.0f, -plane_size / 2)},

		{Vector3D( plane_size / 2,-0.0f, plane_size / 2)},
		{Vector3D( plane_size / 2, 0.0f, plane_size / 2)},
		{Vector3D(-plane_size / 2, 0.0f, plane_size / 2)},
		{Vector3D(-plane_size / 2,-0.0f, plane_size / 2)}
	};

	Vector2D texcoord_list[] =
	{
		{Vector2D(0.0f, 0.0f)},
		{Vector2D(0.0f, 1.0f)},
		{Vector2D(1.0f, 0.0f)},
		{Vector2D(1.0f, 1.0f)},
	};

	vertex vertex_list[] = {
		// X - Y - Z
		// Front Face
		{position_list[0], texcoord_list[1]},
		{position_list[1], texcoord_list[0]},
		{position_list[2], texcoord_list[2]},
		{position_list[3], texcoord_list[3]},

		// Back Face
		{position_list[4], texcoord_list[1]},
		{position_list[5], texcoord_list[0]},
		{position_list[6], texcoord_list[2]},
		{position_list[7], texcoord_list[3]},
	};

	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_vertex_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] = {
		// Front
		//0,1,2,
		//2,3,0,
		// Back
		//4,5,6,
		//6,7,4,
		// Top
		1,6,5,
		5,2,1,
		// Bottom
		7,0,3,
		3,4,7,
		// Right
		//3,2,5,
		//5,4,3,
		// Left
		//7,6,1,
		//1,0,7
	};

	m_ib = GraphicsEngine::Get()->CreateIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->Load(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(&vertex_list, sizeof(vertex), size_vertex_list, shader_byte_code, size_shader);

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

void Plane::Update(float delta_time)
{
	m_angle += 1.57f * delta_time;
	m_delta_scale += delta_time * m_speed;
}

void Plane::Draw(int width, int height)
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
	//cc.m_projection.SetOrthoLH(width / 100.0f, height / 100.0f, -4.0f, 4.0f);
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

	// Set Index Buffer
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetIndexBuffer(m_ib);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawIndexedTriangleList(m_ib->GetSizeIndexList(), 0, 0);
}

Plane::~Plane()
{
	m_vb->Release();
	m_ib->Release();
	m_cb->Release();
	m_vs->Release();
	m_ps->Release();
}

VertexBuffer Plane::GetVertexBuffer()
{
	return *m_vb;
}

void Plane::SetSpeed(float speed)
{
	this->m_speed = speed;
}