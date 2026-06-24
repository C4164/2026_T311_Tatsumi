#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "ComPtr.h"

class CommandAllocator
{
public:
    //コンストラクタとデストラクタ
    CommandAllocator() = default;
    ~CommandAllocator() = default;

    //初期化関数
    bool Init(ID3D12Device* device);

    //ゲッター
    ID3D12CommandAllocator* Get() const { return allocator.Get(); }

private:
    //アロケーター
    ComPtr<ID3D12CommandAllocator> allocator;
};