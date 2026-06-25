#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <cstdint>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh
{
public:
	//コンストラクタとデストラクタ
	Mesh() = default;
	~Mesh() = default;

	//初期化関数
	bool Init(
		ID3D12Device* device,
		ID3D12GraphicsCommandList* commandList
	);

	void SetData(
		void* vtx,
		UINT vtxSize,
		UINT vtxCount,
		uint16_t* idx,
		UINT idxCount
	);

	//描画関数
	void Draw(ID3D12GraphicsCommandList* commandList);

private:
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;

	void* vertices = nullptr;
	UINT vertexSize = 0;
	UINT vertexCount = 0;
	uint16_t* indices = nullptr;
	UINT indexCount = 0;
};
