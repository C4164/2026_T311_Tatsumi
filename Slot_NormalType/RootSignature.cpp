#include "RootSignature.h"
#include <d3d12.h>
#include <d3d12shader.h>
#include <d3dcompiler.h>
#include "d3dx12.h"

bool RootSignature::Init(ID3D12Device* device)
{
    CD3DX12_DESCRIPTOR_RANGE1 srvRange;
    srvRange.Init(
        D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
        1, 0, 0,
        D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC
    );

    CD3DX12_ROOT_PARAMETER1 params[3] = {};

    //TransformCB
    params[0].InitAsConstantBufferView(
        0,
        0,
        D3D12_ROOT_DESCRIPTOR_FLAG_NONE,
        D3D12_SHADER_VISIBILITY_VERTEX
    );

    //CameraCB
    params[1].InitAsConstantBufferView(
        1, 
        0,
        D3D12_ROOT_DESCRIPTOR_FLAG_NONE,
        D3D12_SHADER_VISIBILITY_VERTEX
    );

    //Texture
    params[2].InitAsDescriptorTable(1, &srvRange, D3D12_SHADER_VISIBILITY_PIXEL);

    //Sampler
    D3D12_STATIC_SAMPLER_DESC sampler = {};
    sampler.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
    sampler.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    sampler.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    sampler.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    sampler.ShaderRegister = 0;

    CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC desc;
    desc.Init_1_1(
        _countof(params),
        params,
        1,
        &sampler,
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
    );

    ComPtr<ID3DBlob> sig;
    ComPtr<ID3DBlob> err;

    HRESULT hr = D3DX12SerializeVersionedRootSignature(
        &desc,
        D3D_ROOT_SIGNATURE_VERSION_1_1,
        &sig,
        &err
    );
    if (FAILED(hr)) return false;

    hr = device->CreateRootSignature(
        0,
        sig->GetBufferPointer(),
        sig->GetBufferSize(),
        IID_PPV_ARGS(&rootSignature)
    );

    return SUCCEEDED(hr);
}