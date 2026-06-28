#include "GameScene.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "ObjectFactory.h"



void GameScene::Init()
{
	DeviceManager::Instance().ResetCommandList();

	ResourceManager::LoadTexture(Resource::blankPath);
	ResourceManager::LoadTexture(Resource::bellPath);
	ResourceManager::LoadTexture(Resource::replayPath);
	ResourceManager::LoadTexture(Resource::melonPath);
	ResourceManager::LoadTexture(Resource::cherryPath);
	ResourceManager::LoadTexture(Resource::sevenPath);
	ResourceManager::LoadTexture(Resource::barPath);

	XMFLOAT3 createPos = { -Const::SYMBOLDISTANCE_WIDTH,Const::SYMBOLDISTANCE_HEIGHT,0 };
	XMFLOAT3 createScale = { 1.5f,1.5f,1.5f };

	for (int i = 0; i < Const::REELSYMBOL_NUM; i++)
	{
		Const::Symbols symbol = Const::REELTABLE_LEFT[i];
		leftReelObjects[i] = ObjectFactory::CreateObject(Resource::SymbolPaths[symbol], createPos, createScale);
		createPos.x += Const::SYMBOLDISTANCE_WIDTH;

		symbol = Const::REELTABLE_CENTER[i];
		centerReelObjects[i] = ObjectFactory::CreateObject(Resource::SymbolPaths[symbol], createPos, createScale);
		createPos.x += Const::SYMBOLDISTANCE_WIDTH;

		symbol = Const::REELTABLE_RIGHT[i];
		rightReelObjects[i] = ObjectFactory::CreateObject(Resource::SymbolPaths[symbol], createPos, createScale);
		createPos.x -= Const::SYMBOLDISTANCE_WIDTH * 2.0f;
		createPos.y -= Const::SYMBOLDISTANCE_HEIGHT;
	}

	DeviceManager::Instance().ExecuteCommandList();
}


void GameScene::Update(float deltaTime)
{

}