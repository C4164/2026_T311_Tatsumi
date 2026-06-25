#include "PipelineState.h"
#include "d3dx12.h"
#include "Shader.h"

bool PipelineState::Init(ID3D12Device* device, ID3D12RootSignature* rootSignature)
{
	//入力レイアウト
	static const D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},

		{ 
			"TEXCOORD", 
			0, 
			DXGI_FORMAT_R32G32_FLOAT, 
			0, 
			12,
		    D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 
		    0 
		}
	};

	//シェーダー読み込み
	ID3DBlob* vsBlob = Shader::Instance().LoadVS("Shaders/VS.cso");
	ID3DBlob* psBlob = Shader::Instance().LoadPS("Shaders/PS.cso");

	return Init(
		device,
		rootSignature,
		inputLayout,
		_countof(inputLayout),
		vsBlob,
		psBlob,
		DXGI_FORMAT_R8G8B8A8_UNORM, // RTV フォーマット
		false,                      // Depth 無効
		false                       // AlphaBlend 無効
	);
}

bool PipelineState::Init(
	ID3D12Device* device,
	ID3D12RootSignature* rootSignature,
	const D3D12_INPUT_ELEMENT_DESC* inputLayout,
	UINT inputLayoutCount,
	ID3DBlob* vsBlob,
	ID3DBlob* psBlob,
	DXGI_FORMAT rtvFormat,
	bool enableDepth,
	bool enableAlphaBlend
)
{
	//グラフィックスパイプラインの設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
	desc.pRootSignature = rootSignature;
	//シェーダー
	desc.VS = { vsBlob->GetBufferPointer(), vsBlob->GetBufferSize() };
	desc.PS = { psBlob->GetBufferPointer(), psBlob->GetBufferSize() };
	//入力レイアウト
	desc.InputLayout = { inputLayout, inputLayoutCount };
	//ラスタライザ
	desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	//ブレンド
	if (enableAlphaBlend)
	{
		auto blend = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		blend.RenderTarget[0].BlendEnable = TRUE;
		blend.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
		blend.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
		desc.BlendState = blend;
	}
	else
	{
		desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	}
	//深度ステンシル
	if (enableDepth)
	{
		desc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	}
	else
	{
		desc.DepthStencilState.DepthEnable = FALSE;
		desc.DepthStencilState.StencilEnable = FALSE;
	}
	//サンプルマスク
	desc.SampleMask = UINT_MAX;
	//プリミティブタイプ
	desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	//レンダーターゲット
	desc.NumRenderTargets = 1;
	desc.RTVFormats[0] = rtvFormat;
	desc.SampleDesc.Count = 1;

	//パイプラインステートを作成
	HRESULT hr = device->CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(&pso));
	return SUCCEEDED(hr);
}
