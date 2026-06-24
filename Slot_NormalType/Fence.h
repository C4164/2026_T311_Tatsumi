#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <cstdint>
#include <windows.h>

class Fence
{
public:
    //コンストラクタとデストラクタ
    Fence() = default;
    ~Fence() = default;

    //初期化関数
    bool Init(ID3D12Device* device);
    //GPUに対して命令を進める関数
    void Signal(ID3D12CommandQueue* queue);
    //GPUが処理を完了させるまで待機させる関数
    void Wait();

private:
    Microsoft::WRL::ComPtr<ID3D12Fence> fence;  //フェンス
    uint64_t fenceValue = 0;                    //GPUの進行度
    HANDLE fenceEvent = nullptr;                //イベント
};

