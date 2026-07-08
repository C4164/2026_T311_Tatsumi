#include "UI.h"
#include "ObjectFactory.h"
#include "GameScene.h"
#include "ResourceManager.h"
#include "Resource.h"
#include "Consts.h"
#include "CoinManager.h"

void UI::Init()
{
	//Number
	XMFLOAT3 numberPos(3.0f, 2.5f, 0.0f);
	XMFLOAT3 numberSca(0.5f, 0.7f, 0.5f);
	for (int n = 0; n < 10; n++)
	{

		numbers_ones[n] = ObjectFactory::CreateObject(Resource::NumberPaths[n], numberPos, numberSca);
	}

	numberPos.x -= numberSca.x;
	for (int n = 0; n < 10; n++)
	{
		numbers_tens[n] = ObjectFactory::CreateObject(Resource::NumberPaths[n], numberPos, numberSca);
	}

	numberPos.x -= numberSca.x;
	for (int n = 0; n < 10; n++)
	{
		numbers_hundreds[n] = ObjectFactory::CreateObject(Resource::NumberPaths[n], numberPos, numberSca);
	}

	numberPos.x -= numberSca.x;
	for (int n = 0; n < 10; n++)
	{
		numbers_thousands[n] = ObjectFactory::CreateObject(Resource::NumberPaths[n], numberPos, numberSca);
	}

	XMFLOAT3 minusSca(0.75f, 0.5f, 0.5f);
	numberPos.x -= minusSca.x;
	minus = ObjectFactory::CreateObject(Resource::minusPath, numberPos, minusSca);

	XMFLOAT3 ptPos(3.65f, 2.5f, 0.0f);
	XMFLOAT3 ptSca(1.0f, 1.0f, 0.5f);
	pt = ObjectFactory::CreateObject(Resource::ptPath, ptPos, ptSca);

	//Line
	for (int i = 0; i < 4; i++)
	{
		float y = Const::SYMBOLDISTANCE_HEIGHT * (1.5f - i);
		XMFLOAT3 position(0.0f, y, 0.0f);
		XMFLOAT3 scale(Const::SYMBOLDISTANCE_WIDTH * 3.0f + lineWidth, lineWidth, 0.0f);

		gridLines[i] = ObjectFactory::CreateObject(Resource::whitePath, position, scale);
		GameScene::Instance().AddUIObject(gridLines[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		float x = Const::SYMBOLDISTANCE_WIDTH * (-1.5f + i);
		XMFLOAT3 position(x, 0.0f, 0.0f);
		XMFLOAT3 scale(lineWidth, Const::SYMBOLDISTANCE_HEIGHT * 3.0f + lineWidth, 0.0f);

		gridLines[4 + i] = ObjectFactory::CreateObject(Resource::whitePath, position, scale);
		GameScene::Instance().AddUIObject(gridLines[4 + i]);
	}

	//ChanceLamp
	XMFLOAT3 chancdLampPos(-3.1f, -2.2f, 0.0f);
	XMFLOAT3 chancdLampSca(1.5f, 1.5f, 1.5f);
	chanceLamp_off = ObjectFactory::CreateObject(Resource::chance_offPath, chancdLampPos, chancdLampSca);
	chanceLamp_on = ObjectFactory::CreateObject(Resource::chance_onPath, chancdLampPos, chancdLampSca);
}

void UI::Draw(ID3D12GraphicsCommandList* commandList)const
{
	int num = CoinManager::Instance().GetCoinCount();
	if (num < 0)
	{
		num *= -1;
		minus->Draw(commandList);
	}

	int digits[4];
	digits[0] = (num / 1000) % 10;
	digits[1] = (num / 100) % 10;
	digits[2] = (num / 10) % 10;
	digits[3] = num % 10;

	numbers_thousands[digits[0]]->Draw(commandList);
	numbers_hundreds[digits[1]]->Draw(commandList);
	numbers_tens[digits[2]]->Draw(commandList);
	numbers_ones[digits[3]]->Draw(commandList);

	pt->Draw(commandList);


	//ƒŠ[ƒ‹‚ð‹æØ‚éü‚ð•`‰æ
	for (auto g : gridLines)
	{
		g->Draw(commandList);
	}

	if (chanceLampOn)
	{
		chanceLamp_on->Draw(commandList);
	}
	else
	{
		chanceLamp_off->Draw(commandList);
	}
}