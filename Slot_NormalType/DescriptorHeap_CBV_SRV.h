#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "ComPtr.h"

class DescriptorHeap_CBV_SRV
{
public:
    //コンストラクタとデストラクタ
    DescriptorHeap_CBV_SRV() = default;
    ~DescriptorHeap_CBV_SRV() = default;

    //初期化関数
    bool Init(ID3D12Device* device, UINT numDescriptors);

    //ゲッター
    D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(UINT index) const;
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle(UINT index) const;
    ID3D12DescriptorHeap* GetHeap() const { return heap.Get(); }
    UINT GetDescriptorSize() const { return descriptorSize; }

private:
    ComPtr<ID3D12DescriptorHeap> heap;
    UINT descriptorSize = 0;
};

