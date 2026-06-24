#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <string>
#include "ComPtr.h"

class TextureSRV
{
public:
    //コンストラクタとデストラクタ
    TextureSRV() = default;
    ~TextureSRV() = default;

    //初期化関数
    bool Init(
        ID3D12Device* device,
        ID3D12GraphicsCommandList* commandList,
        const std::wstring& filePath,
        D3D12_CPU_DESCRIPTOR_HANDLE _cpuHandle,
        D3D12_GPU_DESCRIPTOR_HANDLE _gpuHandle
    );

    //ゲッター
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle() const { return gpuHandle; }

private:
    ComPtr<ID3D12Resource> texture;
    ComPtr<ID3D12Resource> uploadBuffer;

    D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = {};
};

