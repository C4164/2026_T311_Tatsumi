#include "ObjectFactory.h"
#include "ResourceManager.h"

GameObject* ObjectFactory::CreateObject(
    const std::wstring& path,
    const XMFLOAT3& pos,
    const XMFLOAT3& scale
)
{
    Mesh* mesh = ResourceManager::GetQuadMesh();
    TextureSRV* tex = ResourceManager::LoadTexture(path);
    PipelineState* pso = ResourceManager::GetSpritePSO();

    Material* mat = new Material();
    mat->SetTexture(tex);
    mat->SetPipelineState(pso);
    mat->Init(DeviceManager::Instance().GetDevice());

    GameObject* obj = new GameObject();
    obj->SetMesh(mesh);
    obj->SetMaterial(mat);
    obj->Init(DeviceManager::Instance().GetDevice());

    obj->transform.position = pos;
    obj->transform.scale = scale;

    Render::Instance().AddObject(obj);
    return obj;
}