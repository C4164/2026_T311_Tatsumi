#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "ComPtr.h"

class CommandQueue 
{
public:
	//コンストラクタとデストラクタ
	CommandQueue() = default;
	~CommandQueue() = default;

	//初期化関数
	bool Init(ID3D12Device* device);

	//ゲッター
	ID3D12CommandQueue* Get()const { return commandQueue.Get(); }

private:
	//コマンドキュー
	ComPtr<ID3D12CommandQueue>commandQueue;
};