#pragma once
#include <windows.h>
#include "DeviceManager.h"
#include "CommandQueue.h"
#include "CommandAllocator.h"
#include "CommandList.h"
#include "Fence.h"
#include "SwapChain.h"
#include "RenderTargetView.h"
#include "RootSignature.h"
#include "PipelineState.h"
#include "DescriptorHeap_SRV.h"
#include "GameObject.h"
#include "Camera.h"
#include "EngineDefs.h"
#include <vector>
#include "ConstantBuffer.h"
#include <stdexcept>

class Render
{
public:
	//シングルトン
	static Render& Instance()
	{
		static Render instance;
		return instance;
	}

	//初期化関数
	bool Init(HWND hwnd, UINT _width, UINT _height);
	void InitCameraCB(ID3D12Device* device)
	{
		camera.aspect = (float)width / (float)height;
		cameraCB.Init(device, sizeof(XMMATRIX));
	}

	//描画関数
	void Draw();

	void AddObject(GameObject* obj, Mesh* mesh, TextureSRV* texture, Material* mat) 
	{
		objects.push_back(obj);
	}

	void InitSceneObjects()
	{
		//それぞれのポインターを取得
		ID3D12Device* device = DeviceManager::Instance().GetDevice();
		ID3D12CommandQueue* queue = commandQueue.Get();

		//コマンドアロケータとコマンドリストをリセット
		commandAllocator.Get()->Reset();
		commandList.Reset(commandAllocator.Get());

		for (auto& obj : objects)
		{
			obj->GetMesh()->Init(device, commandList.Get());
			obj->GetMaterial()->Init(device);
			obj->GetMaterial()->GetTexture()->Init(device, commandList.Get());
			obj->Init(DeviceManager::Instance().GetDevice());
		}

		//コマンドリストを閉じて書き込み終了
		commandList.Close();

		//命令をGPUに送信
		ID3D12CommandList* lists[] = { commandList.Get() };
		queue->ExecuteCommandLists(1, lists);

		//GPUの完了を待つ
		fence.Signal(queue);
		fence.Wait();
	}

	void RegisterTexture(TextureSRV* tex)
	{
		tex->Init(DeviceManager::Instance().GetDevice(), commandList.Get());
	}


private:
	Render() = default;

	//インスタンス
	CommandQueue     commandQueue;
	CommandAllocator commandAllocator;
	CommandList      commandList;
	Fence            fence;
	SwapChain        swapChain;
	RenderTargetView rtv;

	std::vector<GameObject*> objects;

	ConstantBuffer cameraCB;
	Camera camera;

	UINT width = 0;
	UINT height = 0;

	UINT nextSlot = 0;
};
