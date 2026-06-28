#include <windows.h>
#include <thread>
#include <atomic>
#include <chrono>
#include "Input.h"
#include "WindowManager.h"
#include "Render.h"
#include "GameContext.h"
#include "DeviceManager.h"
#include "RootSignature.h"
#include "PipelineState.h"
#include "DescriptorHeap_SRV.h"
#include "GameObject.h"
#include "Camera.h"
#include "EngineDefs.h"
#include "GameScene.h"

//ゲームが実行中かどうかを示すフラグ
//複数のスレッドからアクセスされるため、atomicを使用
std::atomic<bool> running = true;

/// <summary>
/// ゲームのメインスレッドを表す関数
/// </summary>
//void GameThread()
//{
//	//60FPSで動作するループ
//	const float deltaTime = 1.0f / 60.0f;
//	//前回のフレームの時間を保存する変数
//	auto prev = std::chrono::high_resolution_clock::now();
//	//経過時間を保存する変数
//	float accumulator = 0.0f;
//
//	//ゲームが実行中である限りループを続ける
//	while (running)
//	{
//		//現在の時間を取得
//		auto now = std::chrono::high_resolution_clock::now();
//		//前回のフレームからの経過時間を計算
//		float frameTime = std::chrono::duration<float>(now - prev).count();
//		//前回のフレームを更新
//		prev = now;
//
//		//経過時間を蓄積
//		accumulator += frameTime;
//
//		//累積された時間が1フレーム分を超えたらゲームを更新
//		while (accumulator >= deltaTime)
//		{
//			Input::Reset();									//キーの状態をリセット
//			GameContext::Instance().Update(deltaTime);	//ゲームの状態更新
//			accumulator -= deltaTime;						//蓄積時間を減少
//		}
//	}
//}

/// <summary>
/// 描画処理のスレッドを表す関数
/// </summary>
//void RenderThread()
//{
//	Render& render = Render::Instance();
//
//	render.BeginFrame();
//	render.InitSceneObjects();
//	render.EndFrame();
//
//	while (running)
//	{
//		Render::Instance().Draw(); //描画処理
//	}
//}

/// <summary>
/// ウィンドウプロシージャ関数
/// </summary>
/// <param name="hwnd">どのウィンドウに届いたメッセージかを示すハンドル</param>
/// <param name="msg">メッセージの種類</param>
/// <param name="wParam">メッセージの追加情報</param>
/// <param name="lPram">メッセージの追加情報</param>
//ウィンドウプロシージャはOSから多くのメッセージを受け取る
//つまり、OSとゲームエンジンの境界線となる部分
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lPram)
{
	switch (msg)
	{
	case WM_DESTROY:		//ウィンドウが破棄されたときの処理
		running = false;	//ゲームループを終了させる
		PostQuitMessage(0);	//メッセージキューに終了メッセージを送る
		return 0;			//メッセージが処理されたことを示す
	case WM_KEYDOWN:		//キーが押されたとき	
		Input::OnKeyDown((int)wParam);
		return 0;
	case WM_KEYUP:			//キーが離されたとき
		Input::OnKeyUp((int)wParam);
		return 0;
	case WM_SIZE:
		WindowManager::Instance().UpdateSize();
		return 0;
	}
	//デフォルトのウィンドウプロシージャを呼び出す
	return DefWindowProc(hwnd, msg, wParam, lPram);
}

/// <summary>
/// ウィンドウを作成してハンドルを返す関数
/// </summary>
/// <param name="hInstance">WinMainから渡されるアプリケーションインスタンス</param>
HWND CreateGameWindow(HINSTANCE hInstance)
{
	//WNDCLASSはWindowsのウィンドウを作るための設定をまとめた構造体
	//そのインスタンスを作成し、初期化
	WNDCLASS wc = {};

	wc.lpfnWndProc = WndProc;					//ウィンドウプロシージャを設定
	wc.hInstance = hInstance;					//アプリケーションのインスタンスを設定
	wc.lpszClassName = TEXT("GameWindowClass");	//このウィンドウクラスの名前を設定

	//ウィンドウの仕様をOSに宣言
	RegisterClass(&wc);

	//CreateWindowはウィンドウをOSに作らせる関数
	HWND hwnd = CreateWindow(
		wc.lpszClassName,				//RegisterClassに登録したウィンドウクラスの名前
		TEXT("GameWindow"),				//ウィンドウのタイトルバーに表示される文字
		WS_OVERLAPPEDWINDOW,			//ウィンドウのスタイル。今回は一番オーソドックスなもの
		CW_USEDEFAULT, CW_USEDEFAULT,	//ウィンドウの表示位置。CW_USEDEFAULTはOSに適切な位置に任せる形
		800, 600,						//ウィンドウのサイズ
		nullptr, nullptr,				//親ウィンドウとメニューハンドル。ゲームではあまり使わない
		hInstance,						//アプリケーションのインスタンス。RegisterClassを同じものを渡す
		nullptr							//ウィンドウ作成時に渡す追加データ。こちらもゲームではあまり使わない
	);

	//作成したウィンドウを表示
	//SW_SHOWは普通に表示するという意味
	ShowWindow(hwnd, SW_SHOW);
	//ウィンドウのハンドルを返す
	return hwnd;
}

/// <summary>
/// アプリケーションの開始地点を定義する関数
/// </summary>
/// <param name="hInstance">アプリケーションのインスタンス</param>
/// <param name="">前のインスタンス。使わないので名前省略</param>
/// <param name="">コマンドライン引数。使わないので名前省略</param>
/// <param name="">ウィンドウの表示状態。使わないので名前省略</param>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//ウィンドウを作成
	HWND hwnd = CreateGameWindow(hInstance);

	WindowManager::Instance().SetHWND(hwnd);
	WindowManager::Instance().UpdateSize();

	Render& render = Render::Instance();

	//Renderを初期化
	if (!render.Init(hwnd, WindowManager::Instance().Width(), WindowManager::Instance().Height()))
	{
		
	}

	auto device = DeviceManager::Instance().GetDevice();

	//DescriptorHeapを初期化
	DescriptorHeap_SRV::Instance().Init(device, Defs::DESCRIPTOR_COUNT);

	//RootSignatureを初期化
	RootSignature::Instance().Init(device);

	//Cameraを初期化
	render.InitCameraCB(device);

	GameContext::Instance().Init();

	//タイマー
	const float deltaTime = 1.0f / 60.0f;
	auto prev = std::chrono::high_resolution_clock::now();
	float accumulator = 0.0f;

	//MSGはメッセージを格納するための構造体
	//そのインスタンスを作成し、０で初期化
	MSG msg = {};
	//ゲーム実行中ループさせる
	while (running)
	{
		//PeekMessageはメッセージが来ているかをチェックする関数
		//引数nullptrは全てのウィンドウのメッセージを対象とするという意味
		//引数0,0はメッセージの範囲を指定しないをいう意味
		//PM_REMOVEを渡すと一回処理したメッセージは二度と来なくなる
		//つまりこれでOSからのメッセージがある限り処理し続けるようになる
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			//WM_QUITはOSがアプリ終了を要求したかどうか
			//アプリ終了が要求されればゲームを終了させる
			if (msg.message == WM_QUIT) { running = false; }

			//文字入力を対応させる
			TranslateMessage(&msg);
			//取り出したメッセージをウィンドウプロシージャに渡す
			DispatchMessage(&msg);
		}

		//時間計測
		auto now = std::chrono::high_resolution_clock::now();
		float frameTime = std::chrono::duration<float>(now - prev).count();
		prev = now;
		accumulator += frameTime;

		//60FPS更新
		while (accumulator >= deltaTime)
		{
			Input::Reset();
			GameContext::Instance().Update(deltaTime);
			accumulator -= deltaTime;
		}

		//描画
		render.Draw();

		//CPUを1ミリ秒休ませる
		//CPUの無駄な消費を抑えられる
		Sleep(1);
	}

	//アプリケーションを正常に終了させる
	return 0;
}