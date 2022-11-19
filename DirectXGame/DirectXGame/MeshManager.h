#pragma once
#include "ResourceManager.h"

class MeshManager : public ResourceManager
{
public:
	MeshManager();
	~MeshManager();
	Mesh* CreateMeshFromFile(const wchar_t* file_path);
protected:
	virtual Resource* CreateResourceFromFileConcrete(const wchar_t* file_path);
};

