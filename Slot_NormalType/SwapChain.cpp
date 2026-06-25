#include "SwapChain.h"

bool SwapChain::Init(
	IDXGIFactory7* factory,     //ファクトリーのポインター
	ID3D12CommandQueue* queue,  //キューのポインター
	HWND hwnd,                  //ウィンドウハンドル
	UINT width,                 //横幅
	UINT height                 //縦幅
)
{
	//スワップチェーンの情報をまとめる構造体
	DXGI_SWAP_CHAIN_DESC1 desc = {};
	desc.Width = width;                                     //描画する横幅
	desc.Height = height;                                   //描画する縦幅
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;               //カラーフォーマットを設定
	desc.SampleDesc.Count = 1;                              //使わない
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     //リソースを出力レンダーターゲットとして使用
	desc.BufferCount = 2;                                   //バッファーの数(表と裏)
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;        //切り替えの際バックバッファーの内容を破棄

	//スワップチェーン(受け取り専用)
	ComPtr<IDXGISwapChain1> tempSwapChain;

	//スワップチェーンを作成
	HRESULT hr = factory->CreateSwapChainForHwnd(
		queue,          //キューへのポインター
		hwnd,           //ウィンドウハンドル
		&desc,          //構造体へのポインター
		nullptr,        //ウィンドウ化する場合はNULL
		nullptr,        //コンテンツを制限しない
		&tempSwapChain  //スワップチェーンのポインター
	);

	//作成に失敗したらfalseを返して終了
	if (FAILED(hr)) { return false; }

	//IDXGISwapChain1からIDXGISwapChain4に変換
	tempSwapChain.As(&swapChain);

	return true;
}
