#include "CommandAllocator.h"

bool CommandAllocator::Init(ID3D12Device* device)
{
    //アロケーターを作成
    //メモリを確保する
    HRESULT hr = device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT, //アロケーターの種類
        IID_PPV_ARGS(&allocator)        //アロケーターのポインター
    );

    //作成に成功したらtrueを返す
    return SUCCEEDED(hr);
}