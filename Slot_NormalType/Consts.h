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

	//小役の種類数
	constexpr int MINORPRIZE_NUM = 10;

	//設定別の小役確率[分子：16bit(65536)分の何か]
	constexpr std::array<uint16_t, SETTING> BELL{ 5372,5372,5372,5372,5372 };			//ベル
	constexpr std::array<uint16_t, SETTING> REPLAY{ 8978,8978,8978,8978,8978 };			//リプレイ
	constexpr std::array<uint16_t, SETTING> CHANCE{ 365,365,365,365,365 };				//チャンス目
	constexpr std::array<uint16_t, SETTING> MELON_WEAKNESS{ 601,603,619,651,667 };		//弱スイカ
	constexpr std::array<uint16_t, SETTING> MELON_STRENGTH_1{ 120,122,134,146,154 };	//強スイカ1
	constexpr std::array<uint16_t, SETTING> MELON_STRENGTH_2{ 40,40,40,40,40 };			//強スイカ2
	constexpr std::array<uint16_t, SETTING> CHERRY_WEAKNESS{ 600,600,600,600,600 };		//弱チェリー
	constexpr std::array<uint16_t, SETTING> CHERRY_STRENGTH_1{ 252,260,268,276,284 };	//強チェリー1
	constexpr std::array<uint16_t, SETTING> CHERRY_STRENGTH_2{ 60,60,60,60,60 };		//強チェリー2

	//図柄の種類
	constexpr enum Symbols
	{
		blankSymbol = 0,
		bellSymbol,
		replaySymbol,
		melonSymbol,
		cherrySymbol,
		sevenSymbol,
		barSymbol_white,
		barSymbol_black,
	};

	//リール配列
	//1リールの小役数
	constexpr int REELSYMBOL_NUM = 20;

	//左リール
	constexpr std::array<Symbols, REELSYMBOL_NUM> REELTABLE_LEFT
	{
		melonSymbol,
		barSymbol_black,
		cherrySymbol,
		sevenSymbol,
		bellSymbol,
		melonSymbol,
		blankSymbol,
		cherrySymbol,
		replaySymbol,
		bellSymbol,
		melonSymbol,
		barSymbol_white,
		cherrySymbol,
		replaySymbol,
		bellSymbol,
		melonSymbol,
		blankSymbol,
		cherrySymbol,
		replaySymbol,
		bellSymbol
	};
	//中リール
	constexpr std::array<Symbols, REELSYMBOL_NUM> REELTABLE_CENTER
	{
		bellSymbol,
		replaySymbol,
		barSymbol_black,
		bellSymbol,
		cherrySymbol,
		bellSymbol,
		replaySymbol,
		blankSymbol,
		bellSymbol,
		cherrySymbol,
		bellSymbol,
		replaySymbol,
		barSymbol_white,
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
		barSymbol_black,
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
		barSymbol_white,
		cherrySymbol
	};

	//図柄の表示間隔
	constexpr float SYMBOLDISTANCE_WIDTH = 1.5f;	//縦幅
	constexpr float SYMBOLDISTANCE_HEIGHT = 1.25f;	//横幅

	constexpr float REEL_SPEED = 33.0f;				//リールの回転速度
	constexpr float WAIT_TIME = 1.0f;				//ウェイト時間(今のところなし)
	constexpr float REEL_STOPINTERVAL_TIME = 0.2f;	//リール停止間隔時間

	constexpr int SLIDE_SYMBOL_MAX = 5;	//スライドする図柄の数

	//コイン関連
	constexpr int COIN_MAX = 9999;		//最大コイン枚数
	constexpr int COIN_MIN = -9999;	//最小コイン枚数
	constexpr int BET_NUM_NORMAL = 3;	//通常のベット枚数
	constexpr int BET_NUM_BOUNUS = 2;	//ボーナス中のベット枚数
	constexpr int MISS_PAYOUT = 1;		//はずれ目の払い出し枚数
	constexpr int BELL_PAYOUT = 15;		//ベルの払い出し枚数
	constexpr int REPLAY_PAYOUT = 0;	//リプレイの払い出し枚数
	constexpr int MELON_PAYOUT = 5;		//スイカの払い出し枚数
	constexpr int CHERY_PAYOUT = 2;		//チェリーの払い出し枚数

	//モード関連
	constexpr enum Mode
	{
		None = -1,
		LowMode,
		NormalMode,
		HighMode,
		Bonus,
	};

	//リプレイによるモードの転落率(8分の1)
	constexpr int REPLAY_MODE_DOWN = 8192;

	//はずれでのモード別のボーナス当選率
	constexpr int BONUS_HIT_LOW_MODE = 164;
	constexpr int BONUS_HIT_NORMAL_MODE = 328;
	constexpr int BONUS_HIT_HIGH_MODE = 655;

	//モードリセット時の配分
	//低確20%、通常50%、高確30%
	constexpr std::array<int, 3>MODE_RESET_RATE{ 13106, 32768, 19661 };

	struct MODE_TRANS_RATE
	{
		std::array<uint16_t, SETTING> LOW_TO_BOUNUS;	//低確からボーナス
		std::array<uint16_t, SETTING> LOW_TO_HIGH;		//低確から高確
		std::array<uint16_t, SETTING> LOW_TO_NORMAL;	//低確から通常
		std::array<uint16_t, SETTING> NORMAL_TO_BOUNUS;	//通常からボーナス
		std::array<uint16_t, SETTING> NORMAL_TO_HIGH;	//通常から高確
		std::array<uint16_t, SETTING> HIGH_TO_BOUNUS;	//高確からボーナス
	};

	constexpr MODE_TRANS_RATE CHERY_WEAKNESS_TRANS_RATE
	{
		{ 98,105,229,452,708 },
		{ 79,85,111,111,118 },
		{ 3729,3762,5000,5099,5190 },
		{ 184,256,976,1901,2562 },
		{ 2458,2497,3231,3211,3257 },
		{ 1147,1212,2536,3559,4679 }
	};

	constexpr MODE_TRANS_RATE CHERY_STRENGTH_TRANS_RATE
	{
		{ 16383,16383,16383,16383,16383 },
		{ 4096,4096,4096,4096,4096 },
		{ 45056,45056,45056,45056,45056 },
		{ 16384,16384,16384,16384,16384 },
		{ 8192,8192,8192,8192,8192 },
		{ 65535,65535,65535,65535,65535 }
	};

	constexpr MODE_TRANS_RATE MELON_WEAKNESS_TRANS_RATE
	{
		{ 216,249,662,1317,1756 },
		{ 1310,1317,1750,1743,1776 },
		{ 19720,19956,26254,26352,26667 },
		{ 826,911,2386,3316,3952 },
		{ 20441,20565,26300,26083,26273 },
		{ 6986,7065,10499,11705,12557 }
	};

	constexpr MODE_TRANS_RATE MELON_STRENGTH_TRANS_RATE
	{
		{ 4180,4246,4678,5556,5943 },
		{ 16384,16384,16384,16384,16384 },
		{ 44971,44905,44473,43595,43208 },
		{ 6657,6657,6657,6657,6657 },
		{ 58878,58878,58878,58878,58878 },
		{ 32768,32768,32768,32768,32768 }
	};

	constexpr MODE_TRANS_RATE CHANCE_TRANS_RATE
	{
		{ 400,570,1927,3591,4417 },
		{ 125,125,125,125,125 },
		{ 15853,15840,15191,14379,13966 },
		{ 963,983,1311,1619,1874 },
		{ 15421,15781,15643,15473,15349 },
		{ 16384,16384,16384,16384,16384 }
	};
}