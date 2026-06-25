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
#include "DescriptorHeap_CBV_SRV.h"
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
		cameraCB.Init(device, sizeof(XMMATRIX), DescriptorHeap_CBV_SRV::Instance().GetCPUHandle(Defs::CAMERA_SLOT));
	}

	//描画関数
	void Draw();

	void DebugDraw();

	void AddObject(GameObject* obj, Mesh* mesh, TextureSRV* texture, Material* mat)
	{
		auto device = DeviceManager::Instance().GetDevice();
		mesh->Init(device, commandList.Get());
		texture->Init(device, commandList.Get());
		mat->Init(device);

		UINT slot = nextSlot++;

		obj->Init(
			DeviceManager::Instance().GetDevice(),
			DescriptorHeap_CBV_SRV::Instance().GetCPUHandle(slot));

		objects.push_back(obj);
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
