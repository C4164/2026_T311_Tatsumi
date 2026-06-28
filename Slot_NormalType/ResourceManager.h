#pragma once
#include "Render.h"
#include <unordered_map>

class ResourceManager
{
public:
	//ƒVƒ“ƒOƒ‹ƒgƒ“
	static ResourceManager& Instance()
	{
		static ResourceManager instance;
		return instance;
	}

	static TextureSRV* LoadTexture(const std::wstring& path);

	static Mesh* GetQuadMesh();
	static PipelineState* GetSpritePSO();

private:
	ResourceManager() = default;

	static Mesh* CreateQuadMesh();

	Mesh* quadMesh = nullptr;
	PipelineState* spritePSO = nullptr;
	std::unordered_map<std::wstring, TextureSRV*> textures;
};