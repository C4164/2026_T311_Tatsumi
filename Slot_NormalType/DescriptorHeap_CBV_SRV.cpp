#include "DescriptorHeap_CBV_SRV.h"
#include <d3dx12.h>

bool DescriptorHeap_CBV_SRV::Init(ID3D12Device* device, UINT numDescriptors)
{
    //ヒープの作成
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.NumDescriptors = numDescriptors;
    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

    //ディスクリプタヒープを作成し、失敗したらfalseを返して終了
    if (FAILED(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap)))) { return false; }

    //インクリメントするメモリのサイズを取得
    descriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    //正常終了
    return true;
}

//CPUハンドルを取得する関数
D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap_CBV_SRV::GetCPUHandle(UINT index) const
{
    D3D12_CPU_DESCRIPTOR_HANDLE handle = heap->GetCPUDescriptorHandleForHeapStart();
    handle.ptr += index * descriptorSize;
    return handle;
}
//GPUハンドルを取得する関数
D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap_CBV_SRV::GetGPUHandle(UINT index) const
{
    D3D12_GPU_DESCRIPTOR_HANDLE handle = heap->GetGPUDescriptorHandleForHeapStart();
    handle.ptr += index * descriptorSize;
    return handle;
}
