#include "GameScene.h"
#include <string>
#include "PipelineState.h"
#include "DeviceManager.h"

void GameScene::Init()
{
    //Mesh
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
        _countof(indices)
    );

    //Texture
    TextureSRV* texture = new TextureSRV();
    texture->SetPath(L"Data/Texture/chery.png");

    //Material
    Material* mat = new Material();
    mat->SetTexture(texture);

    //
    PipelineState* pso = new PipelineState();
    pso->Init(DeviceManager::Instance().GetDevice(), RootSignature::Instance().Get());
    mat->SetPipelineState(pso);

    // GameObject
    GameObject* obj = new GameObject();
    obj->SetMesh(mesh);
    obj->SetMaterial(mat);
    obj->transform.position = { 0, 0, 0 };
    obj->transform.rotation = { 0, 0, 0 };
    obj->transform.scale = { 100, 100, 100 };

    //Render‚É“o˜^
    Render::Instance().AddObject(obj, mesh, texture, mat);
}


void GameScene::Update(float deltaTime)
{

}

void GameScene::Render()
{

}

void GameScene::End()
{

}