#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "ComPtr.h"

class SwapChain
{
public:
    //コンストラクタとデストラクタ
    SwapChain() = default;
    ~SwapChain() = default;

    //初期化関数
    bool Init(
        IDXGIFactory7* factory,
        ID3D12CommandQueue* queue,
        HWND hwnd,
        UINT width,
        UINT height
    );

    //ゲッター
    IDXGISwapChain4* Get() const { return swapChain.Get(); }
    UINT GetCurrentBackBufferIndex() const { return swapChain->GetCurrentBackBufferIndex(); }

private:
    //スワップチェーン
    ComPtr<IDXGISwapChain4> swapChain;
};

