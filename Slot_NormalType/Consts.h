#pragma once
#include <array>

namespace Const
{
	//小役の種類
	constexpr enum MinorPrize
	{
		bell,				//ベル
		replay,				//リプレイ
		chance,				//チャンス目
		melon_weakness,		//弱スイカ
		melon_strength_1,	//強スイカ1
		melon_strength_2,	//強スイカ2
		cherry_weakness,	//弱チェリー
		cherry_strength_1,	//強チェリー1
		cherry_strength_2,	//強チェリー2
	};

	//設定の段階(数)
	constexpr int SETTING = 5;

	//設定別の小役確率[分子：16bit(65536)分の何か]
	constexpr std::array<int, SETTING> BELL{ 5372 };							//ベル
	constexpr std::array<int, SETTING> REPLAY{ 8978 };							//リプレイ
	constexpr std::array<int, SETTING> CHANCE{ 365 };							//チャンス目
	constexpr std::array<int, SETTING> MELON_WEAKNESS{ 601,603,619,651,667 };	//弱スイカ
	constexpr std::array<int, SETTING> MELON_STRENGTH_1{ 120,122,134,146,154 };	//強スイカ1
	constexpr std::array<int, SETTING> MELON_STRENGTH_2{ 40 };					//強スイカ2
	constexpr std::array<int, SETTING> CHERRY_WEAKNESS{ 600 };					//弱チェリー
	constexpr std::array<int, SETTING> CHERRY_STRENGTH_1{ 252,260,268,276,284 };//強チェリー1
	constexpr std::array<int, SETTING> CHERRY_STRENGTH_2{ 60 };					//強チェリー2

	//図柄の種類
	constexpr enum Symbols 
	{
		blank,
	};

	//リール配列
	//1リールの小役数
	constexpr int REELSYMBOL_NUM = 20;

	//左リール
	constexpr std::array<MinorPrize, REELSYMBOL_NUM> REELTABLE_LEFT
	{

	};
	//中リール
	constexpr std::array<MinorPrize, REELSYMBOL_NUM> REELTABLE_CENTER
	{

	};
	//右リール
	constexpr std::array<MinorPrize, REELSYMBOL_NUM> REELTABLE_RIGHT
	{

	};
}