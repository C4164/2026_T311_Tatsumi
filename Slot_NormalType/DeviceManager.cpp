#include "DeviceManager.h"
#include <iostream>

bool DeviceManager::Init()
{
#if defined(_DEBUG)
	{
		//デバッグ時のみデバッグレイヤーを有効化
		//描画バグやクラッシュなどを未然に防ぐ
		ComPtr<ID3D12Debug>debug;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug))))
		{
			debug->EnableDebugLayer();
		}
	}
#endif

if (!CreateFactory()) { return false; }	//ファクトリーを生成
if (!CreateDevice()) { return false; }	//デバイスを作成
if (!CreateCommandQueue()) { return false; }
if (!CreateCommandList()) { return false; }
if (!fence.Init(device.Get())) { return false; }
return true;
}

bool DeviceManager::CreateFactory()
{
	//DXGIDebug.dll(デバッグ用のダイナミックリンクライブラリ)を読み込むかどうかのフラグ
	UINT flags = 0;
	//デバッグ時のみデバッグレイヤーを有効化
#if defined(_DEBUG)
	flags |= DXGI_CREATE_FACTORY_DEBUG;
#endif
	//ファクトリーを作成し、作成に成功したかどうかを取得
	//作成したフラグとインタフェースポインターを渡す
	HRESULT hr = CreateDXGIFactory2(flags, IID_PPV_ARGS(&factory));

	//負の値以外なら成功
	return SUCCEEDED(hr);
}

bool DeviceManager::CreateDevice()
{
	//アダプター(GPU)
	ComPtr<IDXGIAdapter1>adapter;

	//アダプターの数ループ
	for (UINT i = 0; factory->EnumAdapters1(i, adapter.GetAddressOf()) != DXGI_ERROR_NOT_FOUND; i++)
	{
		//アダプターの情報構造体(ディスクリプタ)
		DXGI_ADAPTER_DESC1 desc;
		//情報を書き込む
		adapter->GetDesc1(&desc);

		//ソフトウェアアダプターを除外
		//CPUによる描画を防ぐ
		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) { continue; }

		//デバイスの作成
		if (SUCCEEDED(D3D12CreateDevice(
			adapter.Get(),			//アダプターのアドレス
			D3D_FEATURE_LEVEL_11_0,	//要求する最低機能レベル(DirectX11相当以上)
			IID_PPV_ARGS(&device)	//作成したデバイスを格納するアドレス
		)))
		{
			return true;
		}
	}
	return false;
}

bool DeviceManager::CreateCommandQueue()
{
	return commandQueue.Init(device.Get());
}

bool DeviceManager::CreateCommandList()
{
	//コマンドアロケータ
	if (!commandAllocator.Init(device.Get())) { return false; }

	//コマンドリスト
	if (!commandList.Init(device.Get(), commandAllocator.Get())) { return false; }

	return true;
}

void DeviceManager::ResetCommandList()
{
	commandList.Reset(commandAllocator.Get());
}

void DeviceManager::ExecuteCommandList()
{
	commandList.Close();

	ID3D12CommandList* lists[] = { commandList.Get() };
	commandQueue.Get()->ExecuteCommandLists(1, lists);

	fence.Signal(commandQueue.Get());
	fence.Wait();
}