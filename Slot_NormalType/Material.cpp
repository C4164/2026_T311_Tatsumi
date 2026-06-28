#include "Material.h"
#include "RootSignature.h"

bool Material::Init(ID3D12Device* device)
{
    if (!pso) { return false; }

    return pso->Init(device, RootSignature::Instance().Get());
}

void Material::Bind(ID3D12GraphicsCommandList* cmdList)
{
    auto rs = RootSignature::Instance().Get();
    if (!rs)
    { 
        OutputDebugStringA("RootSignature Instance null\n");
        return; 
    }

    if (!pso || !pso->Get()) 
    { 
        OutputDebugStringA("PSO null\n");
        return; 
    }

    cmdList->SetGraphicsRootSignature(rs);
    cmdList->SetPipelineState(pso->Get());

    //テクスチャをセット
    if (texture)
    {
        cmdList->SetGraphicsRootDescriptorTable(2, texture->GetGPUHandle());
    }
}


