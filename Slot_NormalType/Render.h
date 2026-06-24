#pragma once
#include <windows.h>
#include "DeviceManager.h"
#include "CommandQueue.h"
#include "CommandAllocator.h"
#include "CommandList.h"
#include "Fence.h"
#include "SwapChain.h"
#include "RenderTargetView.h"

class Render
{
public:
    //シングルトン
    static Render& Instance()
    {
        static Render instance;
        return instance;
    }

    //初期化関数
    bool Init(HWND hwnd, UINT _width, UINT _height);
    //描画関数
    void Draw();

private:
    Render() = default;

    //インスタンス
    DeviceManager    deviceManager;
    CommandQueue     commandQueue;
    CommandAllocator commandAllocator;
    CommandList      commandList;
    Fence            fence;
    SwapChain        swapChain;
    RenderTargetView rtv;

    UINT width = 0;
    UINT height = 0;
};
