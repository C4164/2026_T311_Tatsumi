#pragma once
#include "Random.h"
#include "Consts.h"

//名前の省略
using Const::MinorPrize;

class Flag
{
public:
	//シングルトン
	static Flag& Instance()
	{
		static Flag instance;
		return instance;
	}

	void Init(); //初期化する関数

	MinorPrize FlagUp(const int setting); //フラグを抽選する関数

	//アクセサ
	//現在の小役を取得する関数
	MinorPrize GetCurrentMP()const { return currentMP; }

private:
	Flag() = default;

	Xoroshiro128PP rng;		//乱数生成のインスタンス
	MinorPrize currentMP;	//現在の小役
};