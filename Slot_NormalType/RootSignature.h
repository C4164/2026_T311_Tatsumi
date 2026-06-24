#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "ComPtr.h"

class RootSignature
{
public:
    //コンストラクタとデストラクタ
    RootSignature() = default;
    ~RootSignature() = default;

    //初期化関数
    bool Init(ID3D12Device* device);

    //ゲッター
    ID3D12RootSignature* Get() const { return rootSignature.Get(); }

private:
    ComPtr<ID3D12RootSignature> rootSignature;
};