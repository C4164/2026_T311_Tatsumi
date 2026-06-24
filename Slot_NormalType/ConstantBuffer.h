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
        UINT bufferSize,
        D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle
    );

    //更新関数
    void Update(const void* data, UINT size);

private:
    ComPtr<ID3D12Resource> buffer;  //
    UINT alignedSize = 0;           //
    void* mappedPtr = nullptr;      //
};


