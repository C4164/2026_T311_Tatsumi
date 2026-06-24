#include "GameObject.h"

void GameObject::Draw(ID3D12GraphicsCommandList* commandList)
{
    if (!mesh || !material) return;

    //Transform‚©‚çWorldMatrix‚ðì¬
    XMMATRIX world = transform.GetMatrix();
    XMMATRIX worldT = XMMatrixTranspose(world); // HLSL ‚Í—ñ—Dæ‚È‚Ì‚Å“]’u

    //CBV‚É‘‚«ž‚Þ
    cb.Update(&worldT, sizeof(worldT));

    //b0‚ÉƒoƒCƒ“ƒh
    commandList->SetGraphicsRootConstantBufferView(0, cb.GetGPUAddress());

    // Material¨Mesh‚Ì‡‚Å•`‰æ
    material->Bind(commandList);
    mesh->Draw(commandList);
}
