#include "Cube.h"

Cube::Cube(String name, bool skipInit) : GameObject(name, GameObject::CUBE)
{
	if (skipInit) {
		return;
	}

	// Outline
	float cube_size = 2.0f;
	float outline_scale = 1.1f;

	m_tex = GraphicsEngine::Get()->GetTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\wood.jpg");

	Vector3D position_list[] =
	{
		{Vector3D(-(cube_size / 2),-(cube_size / 2), -(cube_size / 2))},
		{Vector3D(-(cube_size / 2), (cube_size / 2), -(cube_size / 2))},
		{Vector3D((cube_size / 2), (cube_size / 2), -(cube_size / 2))},
		{Vector3D((cube_size / 2),-(cube_size / 2), -(cube_size / 2))},

		{Vector3D((cube_size / 2),-(cube_size / 2), (cube_size / 2))},
		{Vector3D((cube_size / 2), (cube_size / 2), (cube_size / 2))},
		{Vector3D(-(cube_size / 2), (cube_size / 2), (cube_size / 2))},
		{Vector3D(-(cube_size / 2),-(cube_size / 2), (cube_size / 2))}
	};

	Vector2D texcoord_list[] =
	{
		{Vector2D(0.0f, 0.0f)},
		{Vector2D(0.0f, 1.0f)},
		{Vector2D(1.0f, 0.0f)},
		{Vector2D(1.0f, 1.0f)},
	};

	Vector3D color_list[] =
	{
		{Vector3D(1,0.5,0)},
		{Vector3D(0,1,0)},
		{Vector3D(0,0,1)},
		{Vector3D(0,0,0)},

		{Vector3D(1,0,1)},
		{Vector3D(0,1,1)},
		{Vector3D(1,1,0)},
		{Vector3D(1,1,1)},
	};

	/*vertex vertex_list_outline[8] = {
		// X - Y - Z						Color
		// Front Face
		{Vector3D(-(cube_size/2) * outline_scale,-(cube_size/2) * outline_scale,-(cube_size/2) * outline_scale),	Vector3D(1,0.5,0),	Vector3D(1,0.5,0)},
		{Vector3D(-(cube_size/2) * outline_scale, (cube_size/2) * outline_scale,-(cube_size/2) * outline_scale),	Vector3D(1,0.5,0),	Vector3D(1,0.5,0)},
		{Vector3D( (cube_size/2) * outline_scale, (cube_size/2) * outline_scale,-(cube_size/2) * outline_scale),	Vector3D(1,0.5,0),	Vector3D(1,0.5,0)},
		{Vector3D( (cube_size/2) * outline_scale,-(cube_size/2) * outline_scale,-(cube_size/2) * outline_scale),	Vector3D(1,0.5,0),	Vector3D(1,0.5,0)},

		// Back Face
		{Vector3D( (cube_size/2) * outline_scale,-(cube_size/2) * outline_scale, (cube_size/2) * outline_scale),	Vector3D(1,0.5,0),	Vector3D(1,0.5,0)},
		{Vector3D( (cube_size/2) * outline_scale, (cube_size/2) * outline_scale, (cube_size/2) * outline_scale),	Vector3D(1,0.5,0),	Vector3D(1,0.5,0)},
		{Vector3D(-(cube_size/2) * outline_scale, (cube_size/2) * outline_scale, (cube_size/2) * outline_scale),	Vector3D(1,0.5,0),	Vector3D(1,0.5,0)},
		{Vector3D(-(cube_size/2) * outline_scale,-(cube_size/2) * outline_scale, (cube_size/2) * outline_scale),	Vector3D(1,0.5,0),	Vector3D(1,0.5,0)}
	};*/

	vertex vertex_list[] = {
		{position_list[0], texcoord_list[1]},
		{position_list[1], texcoord_list[0]},
		{position_list[2], texcoord_list[2]},
		{position_list[3], texcoord_list[3]},
		
		{position_list[4], texcoord_list[1]},
		{position_list[5], texcoord_list[0]},
		{position_list[6], texcoord_list[2]},
		{position_list[7], texcoord_list[3]},

		{position_list[1], texcoord_list[1]},
		{position_list[6], texcoord_list[0]},
		{position_list[5], texcoord_list[2]},
		{position_list[2], texcoord_list[3]},

		{position_list[7], texcoord_list[1]},
		{position_list[0], texcoord_list[0]},
		{position_list[3], texcoord_list[2]},
		{position_list[4], texcoord_list[3]},

		{position_list[3], texcoord_list[1]},
		{position_list[2], texcoord_list[0]},
		{position_list[5], texcoord_list[2]},
		{position_list[4], texcoord_list[3]},

		{position_list[7], texcoord_list[1]},
		{position_list[6], texcoord_list[0]},
		{position_list[1], texcoord_list[2]},
		{position_list[0], texcoord_list[3]},
	};

	//m_vb_outline = GraphicsEngine::Get()->CreateVertexBuffer();
	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_vertex_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] = {
		// Front
		0,1,2,
		2,3,0,
		// Back
		4,5,6,
		6,7,4,
		// Top
		8,9,10,
		10,11,8,
		// Bottom
		12,13,14,
		14,15,12,
		// Right
		16,17,18,
		18,19,16,
		// Left
		20,21,22,
		22,23,20
	};

	m_ib = GraphicsEngine::Get()->CreateIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->Load(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	//m_vb_outline->Load(&vertex_list_outline, sizeof(cube_vertex), size_vertex_list, shader_byte_code, size_shader);
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

void Cube::Update(float delta_time)
{
	m_angle += 1.57f * delta_time;
	m_delta_scale += delta_time * m_speed;

	//Vector3D local_position = GetLocalPosition();
	//this->SetPosition(local_position.lerp(Vector3D(-1.0f, -1.0f, 0.0f), Vector3D(1.0f, 1.0f, 0.0f), sin(m_delta_scale)));

	//Vector3D local_scale = GetLocalScale();
	//this->SetScale(local_scale.lerp(Vector3D(1.0f, 1.0f, 1.0f), Vector3D(2.0f, 0.0f, 2.0f), abs(sin(m_delta_scale))));
	
	//Vector3D local_rotation = GetLocalRotation();
	//this->SetRotation(m_delta_scale, m_delta_scale, m_delta_scale);
}

void Cube::Draw(int width, int height)
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
	cc.m_projection.SetPerspectiveFovLH(1.57f, (float) width / (float) height, 0.05f, 100.0f);
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
	
	if (GetOutlined())
	{
		// Set Vertex Buffer for outline
		GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb_outline);
		GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawIndexedTriangleList(m_ib->GetSizeIndexList(), 0, 0);
	}

	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawIndexedTriangleList(m_ib->GetSizeIndexList(), 0, 0);
}

Cube::~Cube()
{
	//m_vb_outline->Release();
	m_vb->Release();
	m_ib->Release();
	m_cb->Release();
	m_vs->Release();
	m_ps->Release();
}

VertexBuffer Cube::GetVertexBuffer()
{
	return *m_vb;
}

void Cube::SetSpeed(float speed)
{
	this->m_speed = speed;
}