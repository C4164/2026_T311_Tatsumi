#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "ComPtr.h"

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

	//ゲッター
	ID3D12Device7* GetDevice()const { return device.Get(); }
	IDXGIFactory7* GetFactory()const { return factory.Get(); }

private:
	//コンストラクタ
	DeviceManager() = default;
	~DeviceManager() = default;

	//生成関数
	bool CreateFactory();
	bool CreateDevice();

	//ファクトリー
	ComPtr<IDXGIFactory7>factory = nullptr;
	//デバイス
	ComPtr<ID3D12Device7> device = nullptr;
};