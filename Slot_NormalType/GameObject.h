#pragma once
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "ConstantBuffer.h"

class GameObject
{
public:
    //コンストラクタとデストラクタ
    GameObject() = default;
    ~GameObject() = default;

    //トランスフォーム
    Transform transform;

    //初期化関数
    bool Init(ID3D12Device* device)
    {
        return cb.Init(device, sizeof(XMMATRIX));
    }

    //描画関数
    void Draw(ID3D12GraphicsCommandList* commandList);

    //ゲッター
    Mesh* GetMesh()const { return mesh; }
    Material* GetMaterial()const { return material; }
    //セッター
    void SetMesh(Mesh* m) { mesh = m; }
    void SetMaterial(Material* mat) { material = mat; }

private:
    Mesh* mesh = nullptr;
    Material* material = nullptr;
    ConstantBuffer cb;
};

