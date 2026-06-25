#include "IndexBuffer.h"
#include <d3dx12.h>

bool IndexBuffer::Init(
    ID3D12Device* device,
    ID3D12GraphicsCommandList* commandList,
    const uint16_t* indices,
    UINT indexCount
)
{
    UINT bufferSize = sizeof(uint16_t) * indexCount;

    //GPU側(DEFAULTヒープ)
    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);
    CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

    if (FAILED(device->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&buffer)
    )))
    {
        return false;
    }

    //CPUからGPU転送用(UPLOADヒープ)
    CD3DX12_HEAP_PROPERTIES uploadHeap(D3D12_HEAP_TYPE_UPLOAD);

    if (FAILED(device->CreateCommittedResource(
        &uploadHeap,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&uploadBuffer)
    )))
    {
        return false;
    }

    //転送データ
    D3D12_SUBRESOURCE_DATA subresource = {};
    subresource.pData = indices;
    subresource.RowPitch = bufferSize;
    subresource.SlicePitch = bufferSize;

    //転送する
    UpdateSubresources(commandList, buffer.Get(), uploadBuffer.Get(), 0, 0, 1, &subresource);

    //書き込み専用から読み取り専用に状態遷移
    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        buffer.Get(),
        D3D12_RESOURCE_STATE_COPY_DEST,
        D3D12_RESOURCE_STATE_INDEX_BUFFER
    );
    commandList->ResourceBarrier(1, &barrier);

    //IndexBufferView作成
    view.BufferLocation = buffer->GetGPUVirtualAddress();
    view.SizeInBytes = bufferSize;
    view.Format = DXGI_FORMAT_R16_UINT;

    //正常終了
    return true;
}