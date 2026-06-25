#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "ComPtr.h"

class VertexBuffer
{
public:
    //コンストラクタとデストラクタ
    VertexBuffer() = default;
    ~VertexBuffer() = default;

    //初期化関数
    bool Init(
        ID3D12Device* device,
        ID3D12GraphicsCommandList* commandList,
        const void* vertexData,
        UINT vertexSize,
        UINT vertexCount
    );

    //ゲッター
    const D3D12_VERTEX_BUFFER_VIEW& GetView() const { return view; }

private:
    ComPtr<ID3D12Resource> buffer;
    ComPtr<ID3D12Resource> uploadBuffer;
    D3D12_VERTEX_BUFFER_VIEW view = {};
};
