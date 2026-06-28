#include "GameScene.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "ObjectFactory.h"
#include "Input.h"


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
	const XMFLOAT3 createScale = { 1.5f,1.5f,1.5f };
	const XMFLOAT3 blankScale = { 0.75f,0.75f,0.75f };
	XMFLOAT3 scale = {};
	Const::Symbols symbol;

	for (int i = 0; i < Const::REELSYMBOL_NUM; i++)
	{
		symbol = Const::REELTABLE_LEFT[i];
		scale = (symbol == Const::Symbols::blankSymbol) ? blankScale : createScale;
		leftReelObjects[i] = ObjectFactory::CreateObject(Resource::SymbolPaths[symbol], createPos, scale);
		createPos.x += Const::SYMBOLDISTANCE_WIDTH;

		symbol = Const::REELTABLE_CENTER[i];
		scale = (symbol == Const::Symbols::blankSymbol) ? blankScale : createScale;
		centerReelObjects[i] = ObjectFactory::CreateObject(Resource::SymbolPaths[symbol], createPos, scale);
		createPos.x += Const::SYMBOLDISTANCE_WIDTH;

		symbol = Const::REELTABLE_RIGHT[i];
		scale = (symbol == Const::Symbols::blankSymbol) ? blankScale : createScale;
		rightReelObjects[i] = ObjectFactory::CreateObject(Resource::SymbolPaths[symbol], createPos, scale);
		createPos.x -= Const::SYMBOLDISTANCE_WIDTH * 2.0f;
		createPos.y -= Const::SYMBOLDISTANCE_HEIGHT;
	}

	DeviceManager::Instance().ExecuteCommandList();
}


void GameScene::Update(float deltaTime)
{
	//デバッグ用
	if (Input::IsKeyHold('W'))
	{
		for (int i = 0; i < Const::REELSYMBOL_NUM; i++)
		{
			leftReelObjects[i]->transform.position.y -= 3.0f * deltaTime;
			centerReelObjects[i]->transform.position.y -= 3.0f * deltaTime;
			rightReelObjects[i]->transform.position.y -= 3.0f * deltaTime;
		}
	}
	if (Input::IsKeyHold('S'))
	{
		for (int i = 0; i < Const::REELSYMBOL_NUM; i++)
		{
			leftReelObjects[i]->transform.position.y += 3.0f * deltaTime;
			centerReelObjects[i]->transform.position.y += 3.0f * deltaTime;
			rightReelObjects[i]->transform.position.y += 3.0f * deltaTime;
		}
	}
}