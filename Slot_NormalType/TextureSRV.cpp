#include "TextureSRV.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include "DirectXTex.h"
#include "d3dx12.h"

using namespace DirectX;

bool TextureSRV::Init(
    ID3D12Device* device,                   //デバイスのポインター
    ID3D12GraphicsCommandList* commandList, //コマンドリストのポインター
    const std::wstring& filePath,           //画像のファイルパス
    D3D12_CPU_DESCRIPTOR_HANDLE _cpuHandle,  //CPUハンドル
    D3D12_GPU_DESCRIPTOR_HANDLE _gpuHandle   //GPUハンドル
)
{
    //GPUハンドルを取得
    gpuHandle = _gpuHandle;

    TexMetadata metadata;   //画像の幅や高さなどのデータ
    ScratchImage scratch;   //画像データ本体

    //画像を読み込み
    HRESULT hr = LoadFromWICFile(filePath.c_str(), WIC_FLAGS_NONE, &metadata, scratch);

    //失敗したらfalseを返して終了
    if (FAILED(hr)) { return false; }

    //ピクセルデータを取得
    const Image* img = scratch.GetImage(0, 0, 0);

    //GPU専用メモリであるDEFAULTヒープ
    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);

    //テクスチャの形状を指定
    CD3DX12_RESOURCE_DESC texDesc = CD3DX12_RESOURCE_DESC::Tex2D(
        metadata.format,
        metadata.width,
        metadata.height,
        (UINT16)metadata.arraySize,
        (UINT16)metadata.mipLevels
    );

    //GPUメモリにテクスチャを作成
    hr = device->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &texDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&texture)
    );

    //失敗したらfalseを返して終了
    if (FAILED(hr)) { return false; }

    //転送に必要なバッファサイズを計算
    UINT64 uploadSize = GetRequiredIntermediateSize(texture.Get(), 0, 1);

    //CPUが書き込めるメモリであるUPLOADヒープ
    CD3DX12_HEAP_PROPERTIES uploadHeap(D3D12_HEAP_TYPE_UPLOAD);
    //転送用のバッファー
    CD3DX12_RESOURCE_DESC uploadDesc = CD3DX12_RESOURCE_DESC::Buffer(uploadSize);

    //CPUからGPUへ転送するためのバッファーを作成
    hr = device->CreateCommittedResource(
        &uploadHeap,
        D3D12_HEAP_FLAG_NONE,
        &uploadDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&uploadBuffer)
    );

    //失敗したらfalseを返して終了
    if (FAILED(hr)) { return false; }

    //テクスチャデータをGPUにコピー
    D3D12_SUBRESOURCE_DATA subresource = {};
    subresource.pData = img->pixels;
    subresource.RowPitch = img->rowPitch;
    subresource.SlicePitch = img->slicePitch;
    UpdateSubresources(commandList, texture.Get(), uploadBuffer.Get(), 0, 0, 1, &subresource);

    //書き込み専用から読み取り専用に状態遷移
    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        texture.Get(),
        D3D12_RESOURCE_STATE_COPY_DEST,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
    );
    commandList->ResourceBarrier(1, &barrier);

    //SRVを作成
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = metadata.format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Texture2D.MipLevels = (UINT)metadata.mipLevels;
    device->CreateShaderResourceView(texture.Get(), &srvDesc, _cpuHandle);

    //正常終了
    return true;
}
