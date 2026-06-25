#include "Fence.h"

bool Fence::Init(ID3D12Device* device)
{
    //進行度を初期化
    fenceValue = 0;

    //Fenceを作成
    HRESULT hr = device->CreateFence(
        fenceValue,             //フェンスの初期値
        D3D12_FENCE_FLAG_NONE,  //オプションを設定(指定なし)
        IID_PPV_ARGS(&fence)    //フェンスのポインター
    );

    //作成に失敗したらfalseを返して終了
    if (FAILED(hr)){ return false; }

    //イベントを作成
    fenceEvent = CreateEvent(
        nullptr,    //ハンドルの継承なし
        FALSE,      //自動リセット
        FALSE,      //非署名(イベント通知なし)
        nullptr);   //名前なし

    //イベントの作成に成功したらtrueを返す
    return fenceEvent != nullptr;
}

void Fence::Signal(ID3D12CommandQueue* queue)
{
    //次の値に進める
    fenceValue++;

    //GPUに進行するよう命令
    queue->Signal(fence.Get(), fenceValue);
}

void Fence::Wait()
{
    //GPUの処理がまだなら待機
    if (fence->GetCompletedValue() < fenceValue)
    {
        //発生させるイベントを指定
        fence->SetEventOnCompletion(fenceValue, fenceEvent);
        //待機させる
        WaitForSingleObject(fenceEvent, INFINITE);
    }
}
