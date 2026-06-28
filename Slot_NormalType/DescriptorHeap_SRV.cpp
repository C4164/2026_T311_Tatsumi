#include "DescriptorHeap_SRV.h"
#include <d3dx12.h>
#include "EngineDefs.h"

bool DescriptorHeap_SRV::Init(ID3D12Device* device, UINT numDescriptors)
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

    currentIndex = 0;

    //正常終了
    return true;
}

D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap_SRV::RegistShaderResource(
    ID3D12Device* device,
    ID3D12Resource* resource,
    const D3D12_SHADER_RESOURCE_VIEW_DESC& desc
)
{
    if (currentIndex >= Defs::DESCRIPTOR_COUNT) {
        OutputDebugStringA("ERROR: DescriptorHeap overflow\n");
        return { 0 };
    }

    //CPUハンドルの位置
    D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle =
        heap->GetCPUDescriptorHandleForHeapStart();
    cpuHandle.ptr += (SIZE_T)currentIndex * descriptorSize;

    //GPUハンドルの位置
    D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle =
        heap->GetGPUDescriptorHandleForHeapStart();
    gpuHandle.ptr += (SIZE_T)currentIndex * descriptorSize;

    //SRVを作成
    device->CreateShaderResourceView(resource, &desc, cpuHandle);

    //次のスロットへ
    currentIndex++;

    return gpuHandle;
}

//CPUハンドルを取得する関数
D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap_SRV::GetCPUHandle(UINT index) const
{
    D3D12_CPU_DESCRIPTOR_HANDLE handle = heap->GetCPUDescriptorHandleForHeapStart();
    handle.ptr += index * descriptorSize;
    return handle;
}
//GPUハンドルを取得する関数
D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap_SRV::GetGPUHandle(UINT index) const
{
    D3D12_GPU_DESCRIPTOR_HANDLE handle = heap->GetGPUDescriptorHandleForHeapStart();
    handle.ptr += index * descriptorSize;
    return handle;
}


