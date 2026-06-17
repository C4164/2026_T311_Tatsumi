#pragma once
#include "Random.h"

//小役の種類
enum MinorPrize
{
	bell_1,			//ベル１
	bell_2,			//ベル２
	navigated_bell,	//押し順ベル
	replay_1,		//リプレイ１
	replay_2,		//リプレイ２
	melon_weakness,	//弱スイカ
	melon_strength,	//強スイカ
	cherry_weakness,//弱チェリー
	cherry_strength,//強チェリー
};

class Flag 
{
public:
	Flag() = default;

	void Init();		//初期化する関数

	MinorPrize FlagUp();	//フラグを抽選する関数

	//アクセサ
	//現在の小役を取得する関数
	MinorPrize GetCurrentMP()const { return currentMP; }	

private:
	Xoroshiro128PP rng;		//乱数生成のインスタンス

	MinorPrize currentMP;	//現在の小役
};