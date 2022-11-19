#include "ResourceManager.h"
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#include <iostream>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

Resource* ResourceManager::CreateResourceFromFile(const wchar_t* file_path)
{
	std::wstring full_path = std::experimental::filesystem::absolute(file_path);

	auto it = m_map_resources.find(full_path);

	if (it != m_map_resources.end())
		return it->second;

	Resource* raw_res = this->CreateResourceFromFileConcrete(full_path.c_str());
	if (raw_res)
	{
		Resource* res(raw_res);
		m_map_resources[full_path] = res;
		return res;
	}

	return nullptr;
}

