#include "RenderTargetView.h"

bool RenderTargetView::Init(
	ID3D12Device* device,       //デバイスのポインター
	IDXGISwapChain4* swapChain, //スワップチェーンのポインター
	UINT bufferCount            //バッファーの数
)
{
	//RTV用のディスクリプタヒープ
	//ディスクリプタヒープはディスクリプタを管理する配列
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.NumDescriptors = bufferCount;              //ディスクリプタの数
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;     //RTVを指定
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;   //既定の使用法

	//ディスクリプタヒープを作成出来なければfalseを返して終了
	if (FAILED(device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeap)))) { return false; }

	//ハンドルをインクリメントする際のサイズを取得
	descSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	//バックバッファを格納する配列を確保
	backBuffers.resize(bufferCount);
	rtvHandles.resize(bufferCount);

	//ヒープの開始ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE handle = rtvHeap->GetCPUDescriptorHandleForHeapStart();

	//各バックバッファに対してRTVを作成
	for (UINT i = 0; i < bufferCount; i++)
	{
		//バックバッファを取得
		swapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffers[i]));

		//ハンドルを保存
		rtvHandles[i] = handle;

		//RTVを作成
		device->CreateRenderTargetView(backBuffers[i].Get(), nullptr, handle);

		//次のハンドルへ進める
		handle.ptr += descSize;
	}

	//正常に終了
	return true;
}
