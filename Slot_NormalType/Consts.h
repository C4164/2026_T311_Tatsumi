#pragma once
#include <array>

namespace Const
{
	//小役の種類
	constexpr enum MinorPrize
	{
		nothing,			//はずれ
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
	constexpr std::array<uint16_t, SETTING> BELL{ 5372 };								//ベル
	constexpr std::array<uint16_t, SETTING> REPLAY{ 8978 };								//リプレイ
	constexpr std::array<uint16_t, SETTING> CHANCE{ 365 };								//チャンス目
	constexpr std::array<uint16_t, SETTING> MELON_WEAKNESS{ 601,603,619,651,667 };		//弱スイカ
	constexpr std::array<uint16_t, SETTING> MELON_STRENGTH_1{ 120,122,134,146,154 };	//強スイカ1
	constexpr std::array<uint16_t, SETTING> MELON_STRENGTH_2{ 40 };						//強スイカ2
	constexpr std::array<uint16_t, SETTING> CHERRY_WEAKNESS{ 600 };						//弱チェリー
	constexpr std::array<uint16_t, SETTING> CHERRY_STRENGTH_1{ 252,260,268,276,284 };	//強チェリー1
	constexpr std::array<uint16_t, SETTING> CHERRY_STRENGTH_2{ 60 };					//強チェリー2

	//図柄の種類
	constexpr enum Symbols
	{
		blankSymbol = 0,
		bellSymbol,
		replaySymbol,
		melonSymbol,
		cherrySymbol,
		sevenSymbol,
		barSymbol
	};

	//リール配列
	//1リールの小役数
	constexpr int REELSYMBOL_NUM = 20;

	//左リール
	constexpr std::array<Symbols, REELSYMBOL_NUM> REELTABLE_LEFT
	{
		melonSymbol,
		barSymbol,
		blankSymbol,
		sevenSymbol,
		bellSymbol,
		melonSymbol,
		blankSymbol,
		cherrySymbol,
		replaySymbol,
		bellSymbol,
		melonSymbol,
		barSymbol,
		cherrySymbol,
		replaySymbol,
		bellSymbol,
		melonSymbol,
		blankSymbol,
		blankSymbol,
		replaySymbol,
		bellSymbol
	};
	//中リール
	constexpr std::array<Symbols, REELSYMBOL_NUM> REELTABLE_CENTER
	{
		bellSymbol,
		replaySymbol,
		barSymbol,
		bellSymbol,
		cherrySymbol,
		bellSymbol,
		replaySymbol,
		blankSymbol,
		bellSymbol,
		cherrySymbol,
		bellSymbol,
		replaySymbol,
		barSymbol,
		bellSymbol,
		melonSymbol,
		bellSymbol,
		replaySymbol,
		sevenSymbol,
		bellSymbol,
		melonSymbol
	};
	//右リール
	constexpr std::array<Symbols, REELSYMBOL_NUM> REELTABLE_RIGHT
	{
		replaySymbol,
		blankSymbol,
		bellSymbol,
		barSymbol,
		cherrySymbol,
		replaySymbol,
		melonSymbol,
		bellSymbol,
		sevenSymbol,
		cherrySymbol,
		replaySymbol,
		melonSymbol,
		bellSymbol,
		blankSymbol,
		cherrySymbol,
		replaySymbol,
		blankSymbol,
		bellSymbol,
		barSymbol,
		cherrySymbol
	};

	//図柄の表示間隔
	//縦幅
	constexpr float SYMBOLDISTANCE_WIDTH = 1.5f;
	//横幅
	constexpr float SYMBOLDISTANCE_HEIGHT = 1.25f;
}