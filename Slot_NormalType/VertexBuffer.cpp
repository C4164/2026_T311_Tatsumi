#include "VertexBuffer.h"
#include <d3dx12.h>

bool VertexBuffer::Init(
    ID3D12Device* device,                   //デバイスのポインター
    ID3D12GraphicsCommandList* commandList, //コマンドリストのポインター
    const void* vertexData,                 //頂点配列の先頭ポインター
    UINT vertexSize,                        //1頂点あたりのバイト数
    UINT vertexCount                        //頂点数
)
{
    //頂点バッファの全体のサイズを計算
    UINT bufferSize = vertexSize * vertexCount;

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
    subresource.pData = vertexData;
    subresource.RowPitch = bufferSize;
    subresource.SlicePitch = bufferSize;

    //転送する
    UpdateSubresources(commandList, buffer.Get(), uploadBuffer.Get(), 0, 0, 1, &subresource);

    //書き込み専用から読み取り専用に状態遷移
    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        buffer.Get(),
        D3D12_RESOURCE_STATE_COPY_DEST,
        D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER
    );
    commandList->ResourceBarrier(1, &barrier);

    //VertexBufferViewを作成
    view.BufferLocation = buffer->GetGPUVirtualAddress();
    view.SizeInBytes = bufferSize;
    view.StrideInBytes = vertexSize;

    //正常終了
    return true;
}
