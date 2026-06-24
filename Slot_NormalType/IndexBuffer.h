#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <cstdint>
#include "ComPtr.h"

class IndexBuffer
{
public:
    IndexBuffer() = default;
    ~IndexBuffer() = default;

    bool Init(
        ID3D12Device* device,
        ID3D12GraphicsCommandList* commandList,
        const uint16_t* indices,
        UINT indexCount
    );

    const D3D12_INDEX_BUFFER_VIEW& GetView() const { return view; }

private:
    ComPtr<ID3D12Resource> buffer;
    ComPtr<ID3D12Resource> uploadBuffer;
    D3D12_INDEX_BUFFER_VIEW view = {};
};