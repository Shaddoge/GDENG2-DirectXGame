#include "TextureManager.h"
#include "Texture.h"
#include <iostream>

TextureManager::TextureManager() : ResourceManager()
{
	HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);

	if (FAILED(hr))
		throw std::exception("Texture Manager initialize failed.");
}

TextureManager::~TextureManager()
{
}

Texture* TextureManager::CreateTextureFromFile(const wchar_t* file_path)
{
    return static_cast<Texture*>(CreateResourceFromFile(file_path));
}

Resource* TextureManager::CreateResourceFromFileConcrete(const wchar_t* file_path)
{
	Texture* tex = nullptr;
	try
	{
		tex = new Texture(file_path);
	}
	catch (...) {}

	return tex;
}
