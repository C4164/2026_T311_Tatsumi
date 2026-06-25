#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <string>
#include "TextureSRV.h"
#include "PipelineState.h"

class Material
{
public:
    Material() = default;
    ~Material() = default;

    //GPU初期化
    bool Init(ID3D12Device* device);

    //描画時に呼ぶ
    void Bind(ID3D12GraphicsCommandList* cmdList);

    //セッター
    void SetPipelineState(PipelineState* state) { pso = state; }
    void SetTexture(TextureSRV* tex) { texture = tex; }

private:
    PipelineState* pso = nullptr;
    TextureSRV* texture = nullptr;
};

