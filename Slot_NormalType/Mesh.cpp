#include "Mesh.h"

bool Mesh::Init(
    ID3D12Device* device,
    ID3D12GraphicsCommandList* commandList
)
{
    //VBを初期化
    if (!vertexBuffer.Init(device, commandList, vertices, vertexSize, vertexCount))
    {
        return false;
    }

    //IBを初期化
    if (!indexBuffer.Init(device, commandList, indices, indexCount))
    {
        return false;
    }

    this->indexCount = indexCount;
    return true;
}

void Mesh::SetData(
    void* vtx, 
    UINT vtxSize, 
    UINT vtxCount,
    uint16_t* idx,
    UINT idxCount
) 
{
    vertices = vtx;
    vertexSize = vtxSize;
    vertexCount = vtxCount;
    indices = idx;
    indexCount = idxCount;
}

void Mesh::Draw(ID3D12GraphicsCommandList* commandList)
{
    //VB・IBをセット
    commandList->IASetVertexBuffers(0, 1, &vertexBuffer.GetView());
    commandList->IASetIndexBuffer(&indexBuffer.GetView());

    //描画する
    commandList->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
}
