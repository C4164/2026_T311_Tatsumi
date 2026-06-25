#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <vector>
#include "ComPtr.h"

class RenderTargetView
{
public:
	//コンストラクタとデストラクタ
	RenderTargetView() = default;
	~RenderTargetView() = default;

	//初期化関数
	bool Init(
		ID3D12Device* device,
		IDXGISwapChain4* swapChain,
		UINT bufferCount
	);

	//ゲッター
	D3D12_CPU_DESCRIPTOR_HANDLE GetHandle(UINT index) const { return rtvHandles[index]; }
	ID3D12Resource* GetBuffer(UINT index) const { return backBuffers[index].Get(); }

private:
	//RTVのディスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	//バックバッファの配列
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	//ハンドルの配列
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> rtvHandles;
	//ディスクリプタのサイズ
	UINT descSize = 0;
};

