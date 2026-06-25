#include "Render.h"
#include "d3dx12.h"
#include "EngineDefs.h"

bool Render::Init(HWND hwnd, UINT _width, UINT _height)
{
	//サイズを取得
	width = _width;
	height = _height;

	//デバイス
	if (!DeviceManager::Instance().Init()) { return false; }
	ID3D12Device* device = DeviceManager::Instance().GetDevice();

	//コマンドキュー
	if (!commandQueue.Init(device)) { return false; }

	//コマンドアロケーター
	if (!commandAllocator.Init(device)) { return false; }

	//コマンドリスト
	if (!commandList.Init(device, commandAllocator.Get())) { return false; }

	//フェンス
	if (!fence.Init(device)) { return false; }

	//スワップチェーン
	if (!swapChain.Init(
		DeviceManager::Instance().GetFactory(),
		commandQueue.Get(),
		hwnd,
		width,
		height))
	{
		return false;
	}

	//RTV
	const UINT bufferCount = 2;
	if (!rtv.Init(device, swapChain.Get(), bufferCount)) { return false; }

	return true;
}

void Render::Draw()
{
	//それぞれのポインターを取得
	ID3D12Device* device = DeviceManager::Instance().GetDevice();
	ID3D12CommandQueue* queue = commandQueue.Get();

	//コマンドアロケータとコマンドリストをリセット
	commandAllocator.Get()->Reset();
	commandList.Reset(commandAllocator.Get());

	//現在のバックバッファ
	UINT backBufferIndex = swapChain.GetCurrentBackBufferIndex();
	ID3D12Resource* backBuffer = rtv.GetBuffer(backBufferIndex);
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtv.GetHandle(backBufferIndex);

	//画面表示から描画用に切り替え
	{
		D3D12_RESOURCE_BARRIER barrier =
			CD3DX12_RESOURCE_BARRIER::Transition(
				backBuffer,
				D3D12_RESOURCE_STATE_PRESENT,
				D3D12_RESOURCE_STATE_RENDER_TARGET
			);
		commandList.Get()->ResourceBarrier(1, &barrier);
	}

	//描画範囲を設定
	D3D12_VIEWPORT viewport = {};
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//シザー矩形を設定(画面全体に描画)
	D3D12_RECT scissor = {};
	scissor.left = 0;
	scissor.top = 0;
	scissor.right = static_cast<LONG>(width);
	scissor.bottom = static_cast<LONG>(height);

	//コマンドリストに描画範囲とシザー矩形を設定
	commandList.Get()->RSSetViewports(1, &viewport);
	commandList.Get()->RSSetScissorRects(1, &scissor);

	//描画先を設定
	commandList.Get()->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

	//画面クリア
	float clearColor[] = { 0.1f, 0.2f, 0.4f, 1.0f };
	commandList.Get()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

	//ルートシグネチャ
	if (RootSignature::Instance().Get()) { commandList.Get()->SetGraphicsRootSignature(RootSignature::Instance().Get()); }

	//ディスクリプタヒープ
	if (DescriptorHeap_CBV_SRV::Instance().GetHeap())
	{
		ID3D12DescriptorHeap* heaps[] = { DescriptorHeap_CBV_SRV::Instance().GetHeap() };
		commandList.Get()->SetDescriptorHeaps(1, heaps);
	}

	XMMATRIX vp = camera.GetViewProjMatrix();
	XMMATRIX vpT = XMMatrixTranspose(vp);
	cameraCB.Update(&vpT, sizeof(vpT));

	//b1にバインド(b0 は GameObject の world)
	commandList.Get()->SetGraphicsRootConstantBufferView(1, cameraCB.GetGPUAddress());

	//GameObjectの描画
	for (auto& obj : objects)
	{
		obj->Draw(commandList.Get());
	}

	//描画用から画面表示に切り替え
	{
		D3D12_RESOURCE_BARRIER barrier =
			CD3DX12_RESOURCE_BARRIER::Transition(
				backBuffer,
				D3D12_RESOURCE_STATE_RENDER_TARGET,
				D3D12_RESOURCE_STATE_PRESENT
			);
		commandList.Get()->ResourceBarrier(1, &barrier);
	}

	//コマンドリストを閉じて書き込み終了
	commandList.Close();

	//命令をGPUに送信
	ID3D12CommandList* lists[] = { commandList.Get() };
	queue->ExecuteCommandLists(1, lists);

	//GPUの完了を待つ
	fence.Signal(queue);
	fence.Wait();

	//画面に表示
	swapChain.Get()->Present(1, 0);
}

