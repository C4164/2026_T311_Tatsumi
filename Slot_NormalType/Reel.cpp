#include "Reel.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "ObjectFactory.h"
#include "Input.h"
#include "GameScene.h"
#include "Flag.h"
#include <cmath>

void Reel::Init()
{
	//それぞれのテクスチャーをロード
	ResourceManager::LoadTexture(Resource::blankPath);
	ResourceManager::LoadTexture(Resource::bellPath);
	ResourceManager::LoadTexture(Resource::replayPath);
	ResourceManager::LoadTexture(Resource::melonPath);
	ResourceManager::LoadTexture(Resource::cherryPath);
	ResourceManager::LoadTexture(Resource::sevenPath);
	ResourceManager::LoadTexture(Resource::bar_whitePath);
	ResourceManager::LoadTexture(Resource::bar_blackPath);

	//図柄を作成し、リール配列通りに配置
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
		GameScene::Instance().AddGameObject(leftReelObjects[i]);
		createPos.x += Const::SYMBOLDISTANCE_WIDTH;

		symbol = Const::REELTABLE_CENTER[i];
		scale = (symbol == Const::Symbols::blankSymbol) ? blankScale : createScale;
		centerReelObjects[i] = ObjectFactory::CreateObject(Resource::SymbolPaths[symbol], createPos, scale);
		GameScene::Instance().AddGameObject(centerReelObjects[i]);
		createPos.x += Const::SYMBOLDISTANCE_WIDTH;

		symbol = Const::REELTABLE_RIGHT[i];
		scale = (symbol == Const::Symbols::blankSymbol) ? blankScale : createScale;
		rightReelObjects[i] = ObjectFactory::CreateObject(Resource::SymbolPaths[symbol], createPos, scale);
		GameScene::Instance().AddGameObject(rightReelObjects[i]);
		createPos.x -= Const::SYMBOLDISTANCE_WIDTH * 2.0f;
		createPos.y -= Const::SYMBOLDISTANCE_HEIGHT;
	}
}

void Reel::Update(float deltaTime)
{
	reelStopTimer += deltaTime;
	waitTimer += deltaTime;

	ActionCheck();

	ReelStop(deltaTime, leftReelObjects, isSpinLeft, isStopLeft);
	ReelStop(deltaTime, centerReelObjects, isSpinCenter, isStopCenter);
	ReelStop(deltaTime, rightReelObjects, isSpinRight, isStopRight);

	UpdatePosition(deltaTime, leftReelObjects, isSpinLeft, isStopLeft);
	UpdatePosition(deltaTime, centerReelObjects, isSpinCenter, isStopCenter);
	UpdatePosition(deltaTime, rightReelObjects, isSpinRight, isStopRight);
}

void Reel::ActionCheck()
{
	//スペースキーが押されていなければ何もしない
	if (!Input::IsKeyDown(VK_SPACE)) { return; }

	//第一停止
	if (isSpinLeft && reelStopTimer > Const::REEL_STOPINTERVAL_TIME)
	{
		isStopLeft = true;
		SetStopIndex(leftReelObjects);
		SetTargetIndex_Left();
	}
	//第二停止
	else if (isSpinCenter && reelStopTimer > Const::REEL_STOPINTERVAL_TIME)
	{
		isStopCenter = true;
		SetStopIndex(centerReelObjects);
		SetTargetIndex_Center();
	}
	//第三停止
	else if (isSpinRight && reelStopTimer > Const::REEL_STOPINTERVAL_TIME)
	{
		isStopRight = true;
		SetStopIndex(rightReelObjects);
		SetTargetIndex_Right();
	}
	//リール始動
	else if (waitTimer > Const::WAIT_TIME)
	{
		minorPrize = Flag::Instance().FlagUp(4);

		//デバッグ用小役指定
		if (Input::IsKeyHold('1'))
		{
			minorPrize = Const::bell;
		}
		else if (Input::IsKeyHold('2'))
		{
			minorPrize = Const::replay;
		}
		else if (Input::IsKeyHold('3'))
		{
			minorPrize = Const::chance;
		}
		else if (Input::IsKeyHold('4'))
		{
			minorPrize = Const::melon_weakness;
		}
		else if (Input::IsKeyHold('5'))
		{
			minorPrize = Const::melon_strength_1;
		}
		else if (Input::IsKeyHold('6'))
		{
			minorPrize = Const::cherry_weakness;
		}
		else if (Input::IsKeyHold('7'))
		{
			minorPrize = Const::cherry_strength_1;
		}

		OutputDebugStringA(("minorPrize: " + std::to_string(minorPrize) + "\n").c_str());

		isSpinLeft = true;
		isSpinCenter = true;
		isSpinRight = true;

		isStopLeft = false;
		isStopCenter = false;
		isStopRight = false;

		reelStopTimer = 0.0f;
		waitTimer = 0.0f;
	}
}

void Reel::UpdatePosition(
	float deltaTime,
	std::array<GameObject*, Const::REELSYMBOL_NUM> reelObjects,
	bool isSpin,
	bool isStop)
{
	//リール回転中のみ移動
	if (!isSpin) { return; }

	for (int i = 0; i < Const::REELSYMBOL_NUM; i++)
	{
		//速度分移動
		reelObjects[i]->transform.position.y -= Const::REEL_SPEED * deltaTime;
		//一番下までいったら上まで移動してサイクルさせる
		if (reelObjects[i]->transform.position.y < down)
		{
			reelObjects[i]->transform.position.y += Const::SYMBOLDISTANCE_HEIGHT * Const::REELSYMBOL_NUM;
		}
	}
}

void Reel::ReelStop(
	float deltaTime,
	std::array<GameObject*, Const::REELSYMBOL_NUM> reelObjects,
	bool& isSpin,
	bool isStop)
{
	//リールが回転中かつ停止ボタンが押されている状態
	if (!isSpin) { return; }
	if (!isStop) { return; }

	//このフレームにオブジェクトが中段位置を超えるなら正しい位置にぴったり吸着させる
	if (reelObjects[targetIndex]->transform.position.y - Const::REEL_SPEED * deltaTime < 0.0f)
	{
		float stopPosY = Const::SYMBOLDISTANCE_HEIGHT;
		int index = (targetIndex - 1 + Const::REELSYMBOL_NUM) % Const::REELSYMBOL_NUM;
		//全てのオブジェクトを吸着させる
		for (int i = 0; i < Const::REELSYMBOL_NUM; i++)
		{
			reelObjects[index]->transform.position.y = stopPosY;
			stopPosY -= Const::SYMBOLDISTANCE_HEIGHT;
			index = (index + 1) % Const::REELSYMBOL_NUM;
		}
		//リールを停止
		isSpin = false;
		targetIndex = -1;
	}
}

void Reel::SetTargetIndex_Left()
{
	if (stopIndex == -1) { return; }

	//弱スイカは0番目の図柄(スイカ)を中段に止める
	if (minorPrize == Const::melon_weakness)
	{
		targetIndex = TargetIndexCalc(stopIndex, 0);
	}
	//弱チェリー、強スイカは1番目の図柄(バー、ブランク)を中段に止める
	else if (
		minorPrize == Const::melon_strength_1 ||
		minorPrize == Const::melon_strength_2 ||
		minorPrize == Const::cherry_weakness
		)
	{
		targetIndex = TargetIndexCalc(stopIndex, 1);
	}
	//強チェリーは2番目の図柄(チェリー)を中段に止める
	else if (
		minorPrize == Const::cherry_strength_1 ||
		minorPrize == Const::cherry_strength_2
		)
	{
		targetIndex = TargetIndexCalc(stopIndex, 2);
	}
	//はずれ、ベル、リプレイ、チャンス目は4番目の図柄(ベル)を中段に止める
	else if (
		minorPrize == Const::nothing ||
		minorPrize == Const::bell ||
		minorPrize == Const::replay ||
		minorPrize == Const::chance
		)
	{
		targetIndex = TargetIndexCalc(stopIndex, 4);
	}

	stopIndex = -1;
}

void Reel::SetTargetIndex_Center()
{
	if (stopIndex == -1) { return; }

	//ベル、チャンス目、強スイカは0番目の図柄(ベル)を中段に止める
	if (
		minorPrize == Const::bell ||
		minorPrize == Const::chance ||
		minorPrize == Const::melon_strength_1 ||
		minorPrize == Const::melon_strength_2
		)
	{
		targetIndex = TargetIndexCalc(stopIndex, 0);
	}
	//はずれは1番目の図柄(リプレイ)を中段に止める
	else if (minorPrize == Const::nothing)
	{
		targetIndex = TargetIndexCalc(stopIndex, 1);
	}
	//リプレイ、強チェリー、弱チェリーは2番目の図柄(バー、ブランク、ボーナス)を中段に止める
	else if (
		minorPrize == Const::replay ||
		minorPrize == Const::cherry_strength_1 ||
		minorPrize == Const::cherry_strength_2 ||
		minorPrize == Const::cherry_weakness
		)
	{
		targetIndex = TargetIndexCalc(stopIndex, 2);
	}
	//弱スイカは4番目の図柄(スイカ、チェリー)を中段に止める
	else if (
		minorPrize == Const::melon_weakness
		)
	{
		targetIndex = TargetIndexCalc(stopIndex, 4);
	}

	stopIndex = -1;
}

void Reel::SetTargetIndex_Right()
{
	if (stopIndex == -1) { return; }

	//リプレイ、弱スイカは1番目の図柄(スイカ、ブランク)を中段に止める
	else if (
		minorPrize == Const::replay ||
		minorPrize == Const::melon_weakness
		)
	{
		targetIndex = TargetIndexCalc(stopIndex, 1);
	}
	//ベル、強スイカは2番目の図柄(ベル)を中段に止める
	else if (
		minorPrize == Const::bell ||
		minorPrize == Const::melon_strength_1 ||
		minorPrize == Const::melon_strength_2)
	{
		targetIndex = TargetIndexCalc(stopIndex, 2);
	}
	//はずれ、チャンス目は3番目の図柄(バー、ボーナス、ブランク)を中段に止める
	else if (
		minorPrize == Const::nothing ||
		minorPrize == Const::chance
		)
	{
		targetIndex = TargetIndexCalc(stopIndex, 3);
	}
	//強チェリー、弱チェリーは4番目の図柄(チェリー)を中段に止める
	else if (
		minorPrize == Const::cherry_strength_1 ||
		minorPrize == Const::cherry_strength_2 ||
		minorPrize == Const::cherry_weakness
		)
	{
		targetIndex = TargetIndexCalc(stopIndex, 4);
	}

	stopIndex = -1;
}

int Reel::TargetIndexCalc(int stopIdx, int target)
{
	int current = stopIdx % Const::SLIDE_SYMBOL_MAX + Const::SLIDE_SYMBOL_MAX;

	int targetIdx = stopIdx - (current - target) % Const::SLIDE_SYMBOL_MAX;
	if (targetIdx < 0) { targetIdx += Const::REELSYMBOL_NUM; }

	return targetIdx;
}

void Reel::SetStopIndex(std::array<GameObject*, Const::REELSYMBOL_NUM> reelObjects)
{
	if (stopIndex != -1) { return; }

	for (int i = 0; i < Const::REELSYMBOL_NUM; i++)
	{
		if (reelObjects[i]->transform.position.y < 1.5f &&
			reelObjects[i]->transform.position.y > 0.0f)
		{
			stopIndex = i;
			break;
		}
	}
}