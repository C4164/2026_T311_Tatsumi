#include "RootSignature.h"
#include <d3d12.h>
#include <d3d12shader.h>
#include <d3dcompiler.h>
#include "d3dx12.h"

bool RootSignature::Init(ID3D12Device* device)
{
    //CBV(定数バッファ)
    CD3DX12_DESCRIPTOR_RANGE1 cbvRange;
    cbvRange.Init(
        D3D12_DESCRIPTOR_RANGE_TYPE_CBV,
        1, 0,
        0,
        D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC
    );

    //SRV(テクスチャー)
    CD3DX12_DESCRIPTOR_RANGE1 srvRange;
    srvRange.Init(
        D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
        1, 0,
        0,
        D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC
    );

    //ルートパラメータ(CBV+SRV)
    CD3DX12_ROOT_PARAMETER1 rootParams[2];

    //CBV用のディスクリプタテーブル
    rootParams[0].InitAsDescriptorTable(1, &cbvRange, D3D12_SHADER_VISIBILITY_VERTEX);

    //SRV用のディスクリプタテーブル
    rootParams[1].InitAsDescriptorTable(1, &srvRange, D3D12_SHADER_VISIBILITY_PIXEL);

    //サンプラー
    D3D12_STATIC_SAMPLER_DESC sampler = {};
    sampler.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
    sampler.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    sampler.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    sampler.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    sampler.ShaderRegister = 0;

    //ルートシグネチャの情報をまとめる構造体
    CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC desc;
    desc.Init_1_1(
        _countof(rootParams),
        rootParams,
        1,
        &sampler,
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
    );

	//バイナリ形式(二進数や生データ)に変換するためのバッファ
	ComPtr<ID3DBlob> signatureBlob;
	ComPtr<ID3DBlob> errorBlob;

	//バイナリ形式に変換
    HRESULT hr = D3DX12SerializeVersionedRootSignature(
        &desc,
        D3D_ROOT_SIGNATURE_VERSION_1_1,
        &signatureBlob,
        &errorBlob
    );

	//失敗したらfalseを返して終了
	if (FAILED(hr)) { return false; }

	//ルートシグネチャを作成
	hr = device->CreateRootSignature(
		0,
		signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature)
	);

	return SUCCEEDED(hr);
}


