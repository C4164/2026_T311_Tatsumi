#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "ComPtr.h"

class ConstantBuffer
{
public:
    //コンストラクタとデストラクタ
    ConstantBuffer() = default;
    ~ConstantBuffer() = default;

    //初期化関数
    bool Init(
        ID3D12Device* device,
        UINT bufferSize
    );

    //更新関数
    void Update(const void* data, UINT size);

    D3D12_GPU_VIRTUAL_ADDRESS GetGPUAddress() const
    {
        return buffer->GetGPUVirtualAddress();
    }

private:
    ComPtr<ID3D12Resource> buffer;  //
    UINT alignedSize = 0;           //
    void* mappedPtr = nullptr;      //
};


