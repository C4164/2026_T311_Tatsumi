#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "ComPtr.h"

class CommandList
{
public:
    //コンストラクタとデストラクタ
    CommandList() = default;
    ~CommandList() = default;

    //初期化関数
    bool Init(ID3D12Device* device, ID3D12CommandAllocator* allocator); 
    //リセット関数
    void Reset(ID3D12CommandAllocator* allocator);                      
    //描画命令完了を知らせる関数
    void Close();                                                       

    //ゲッター
    ID3D12GraphicsCommandList* Get() const { return commandList.Get(); }

private:
    //コマンドリスト
    ComPtr<ID3D12GraphicsCommandList> commandList;
};
