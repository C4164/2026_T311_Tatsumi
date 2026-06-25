#include "CommandQueue.h"

bool CommandQueue::Init(ID3D12Device* device) 
{
	//キューの情報を設定する構造体（ディスクリプタ）
	D3D12_COMMAND_QUEUE_DESC desc = {};					//コマンドリストの種類を指定
	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;			//描画命令を実行できるキュー
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;//キューの優先度はノーマル
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;			//既定のキュー
	desc.NodeMask = 0;									//単一GPU操作

	//デバイスからコマンドキューを作成
	HRESULT hr = device->CreateCommandQueue(&desc, IID_PPV_ARGS(&commandQueue));

	//作成に成功ならtrueを返す
	return SUCCEEDED(hr);
}