#include "GameScene.h"
#include "DeviceManager.h"
#include "Render.h"
#include "Flag.h"
#include "ModeSelection.h"

void GameScene::Init()
{
	DeviceManager::Instance().ResetCommandList();

	Flag::Instance().Init();
	ModeSelection::Instance().Init();

	UI::Instance().Init();
	reel.Init(setting);
	ModeSelection::Instance().ResetMode();

	DeviceManager::Instance().ExecuteCommandList();

	int centerX = Render::Instance().GetWidth() / 2;
	int centerY = Render::Instance().GetHeight() / 2;

	int halfWidth = 250;
	int halfHeight = 180;

	reelScissor.left = centerX - halfWidth;
	reelScissor.right = centerX + halfWidth;
	reelScissor.top = centerY - halfHeight;
	reelScissor.bottom = centerY + halfHeight;

	fullScissor.left = 0;
	fullScissor.top = 0;
	fullScissor.right = static_cast<LONG>(Render::Instance().GetWidth());
	fullScissor.bottom = static_cast<LONG>(Render::Instance().GetHeight());
}


void GameScene::Update(float deltaTime)
{
	reel.Update(deltaTime);
}

void GameScene::DrawObjects(ID3D12GraphicsCommandList* commandList)
{
	commandList->RSSetScissorRects(1, &reelScissor);

	for (auto o : gameObjects)
	{
		o->Draw(commandList);
	}

	commandList->RSSetScissorRects(1, &fullScissor);
}

void GameScene::DrawUI(ID3D12GraphicsCommandList* commandList)
{
	UI::Instance().Draw(commandList);
}