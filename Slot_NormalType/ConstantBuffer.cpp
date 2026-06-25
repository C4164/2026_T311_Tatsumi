#include "ConstantBuffer.h"
#include "d3dx12.h"

bool ConstantBuffer::Init(
	ID3D12Device* device,                   //デバイスのポインター
	UINT bufferSize,                        //定数バッファーのサイズ
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle   //CPUのハンドル
)
{
	//256バイトの倍数分確保
	alignedSize = (bufferSize + 255) & ~255;

	//CPUから書き込めるメモリを指定
	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
	//バッファーのサイズ分リソースを作成
	CD3DX12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(alignedSize);

	//GPUリソースを作成
	HRESULT hr = device->CreateCommittedResource(
		&heapProps,                         //リソースのヒープのプロパティ構造体へのポインター
		D3D12_HEAP_FLAG_NONE,               //ヒープのオプション(指定なし)
		&desc,                              //リソースの構造体へのポインター
		D3D12_RESOURCE_STATE_GENERIC_READ,  //アップロードヒープに必要な開始状態を設定
		nullptr,                            //クリアカラーの規定値構造体(指定なし)
		IID_PPV_ARGS(&buffer)               //バッファーのポインター
	);

	//失敗したらfalseを返して終了
	if (FAILED(hr)) { return false; }

	//CPUから書き込めるようマッピングする
	hr = buffer->Map(0, nullptr, &mappedPtr);

	//失敗したらfalseを返して終了
	if (FAILED(hr)) { return false; }

	//CBVの情報をまとめる構造体
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
	//GPUがバッファーを読むためのアドレス
	cbvDesc.BufferLocation = buffer->GetGPUVirtualAddress();
	//サイズを設定
	cbvDesc.SizeInBytes = alignedSize;

	//CPUハンドルにCBVを作成
	device->CreateConstantBufferView(&cbvDesc, cpuHandle);

	//正常終了
	return true;
}

void ConstantBuffer::Update(const void* data, UINT size)
{
	//GPUへデータをコピー
	memcpy(mappedPtr, data, size);
}

