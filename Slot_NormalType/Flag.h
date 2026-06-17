#pragma once
#include "Consts.h"

//名前の省略
using Const::MinorPrize;

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
	MinorPrize currentMP;	//現在の小役
};