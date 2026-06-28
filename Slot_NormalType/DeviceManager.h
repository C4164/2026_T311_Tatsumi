#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "ComPtr.h"
#include "CommandAllocator.h"
#include "CommandList.h"
#include "CommandQueue.h"
#include "Fence.h"

class DeviceManager
{
public:
	//シングルトン
	static DeviceManager& Instance()
	{
		static DeviceManager instance;
		return instance;
	}

	//初期化関数
	bool Init();

	void ResetCommandList();
	void ExecuteCommandList();

	//ゲッター
	ID3D12Device7* GetDevice()const { return device.Get(); }
	IDXGIFactory7* GetFactory()const { return factory.Get(); }
	ID3D12CommandQueue* GetCommandQueue() { return commandQueue.Get(); }
	ID3D12GraphicsCommandList* GetCommandList() { return commandList.Get(); }

private:
	//コンストラクタ
	DeviceManager() = default;
	~DeviceManager() = default;

	//生成関数
	bool CreateFactory();
	bool CreateDevice();
	bool CreateCommandQueue();
	bool CreateCommandList();

	//ファクトリー
	ComPtr<IDXGIFactory7>factory = nullptr;
	//デバイス
	ComPtr<ID3D12Device7> device = nullptr;
	//初期化用コマンドアロケーター・リスト
	CommandAllocator commandAllocator;
	CommandList commandList;
	//コマンドキュー
	CommandQueue commandQueue;
	//フェンス
	Fence fence;
};