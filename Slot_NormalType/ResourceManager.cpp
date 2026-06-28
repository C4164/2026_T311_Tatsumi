#include "ResourceManager.h"



TextureSRV* ResourceManager::LoadTexture(const std::wstring& path)
{
    auto& inst = Instance();

    auto it = inst.textures.find(path);
    if (it != inst.textures.end())
        return it->second;

    TextureSRV* tex = new TextureSRV();
    tex->SetPath(path);
    tex->Init(
        DeviceManager::Instance().GetDevice(),
        DeviceManager::Instance().GetCommandList()
    );

    inst.textures[path] = tex;
    return tex;
}

Mesh* ResourceManager::GetQuadMesh()
{
    auto& inst = Instance();
    if (!inst.quadMesh)
    {
        inst.quadMesh = CreateQuadMesh();
    }
    return inst.quadMesh;
}

PipelineState* ResourceManager::GetSpritePSO()
{
    auto& inst = Instance();
    if (!inst.spritePSO)
    {
        inst.spritePSO = new PipelineState();
        inst.spritePSO->Init(
            DeviceManager::Instance().GetDevice(),
            RootSignature::Instance().Get()
        );
    }
    return inst.spritePSO;
}

Mesh* ResourceManager::CreateQuadMesh()
{
    struct Vertex { XMFLOAT3 pos; XMFLOAT2 uv; };

    Vertex vertices[] =
    {
        {{-0.5f,  0.5f, 0}, {0,0}},
        {{ 0.5f,  0.5f, 0}, {1,0}},
        {{ 0.5f, -0.5f, 0}, {1,1}},
        {{-0.5f, -0.5f, 0}, {0,1}},
    };

    uint16_t indices[] = { 0,1,2, 0,2,3 };

    Mesh* mesh = new Mesh();
    mesh->SetData(
        vertices,
        sizeof(Vertex),
        _countof(vertices),
        indices,
        _countof(indices));
    mesh->Init(
        DeviceManager::Instance().GetDevice(),
        DeviceManager::Instance().GetCommandList()
    );
    return mesh;
}