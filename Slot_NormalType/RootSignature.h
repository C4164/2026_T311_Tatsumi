#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "ComPtr.h"

class RootSignature
{
public:
    //シングルトン
    static RootSignature& Instance()
    {
        static RootSignature instance;
        return instance;
    }

    //初期化関数
    bool Init(ID3D12Device* device);

    //ゲッター
    ID3D12RootSignature* Get() const { return rootSignature.Get(); }

private:
    //コンストラクタ
    RootSignature() = default;

    ComPtr<ID3D12RootSignature> rootSignature;
};