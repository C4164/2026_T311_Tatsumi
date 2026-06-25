#include "CommandList.h"

bool CommandList::Init(ID3D12Device* device, ID3D12CommandAllocator* allocator)
{
    HRESULT hr = device->CreateCommandList(
        0,                              //単一のGPU操作
        D3D12_COMMAND_LIST_TYPE_DIRECT, //コマンドリストの種類
        allocator,                      //アロケーターのポインター
        nullptr,                        //パイプライン状態のポインター(設定しない)
        IID_PPV_ARGS(&commandList)      //コマンドリストのポインター
    );

    //作成に成功したら書き込みができないようにしてからtrueを返す
    if (SUCCEEDED(hr))
    {
        commandList->Close();
        return true;
    }

    return false;
}

void CommandList::Reset(ID3D12CommandAllocator* allocator)
{
    //書き込みが可能な状態にする
    commandList->Reset(allocator, nullptr);
}

void CommandList::Close()
{
    //書き込みできないようにする
    commandList->Close();
}
