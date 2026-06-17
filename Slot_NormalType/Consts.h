#pragma once

namespace Const
{
	//設定の段階(数)
	constexpr int SETTING = 6;

	//設定別の小役確率[分子：16bit(65536)分の何か]
	struct Probability
	{
		const int BELL[SETTING] = { 0,0,0,0,0,0 };				//ベル
		const int REPLAY[SETTING] = { 0,0,0,0,0,0 };			//リプレイ
		const int CHANCE[SETTING] = { 0,0,0,0,0,0 };			//チャンス目
		const int MELON_WEAKNESS[SETTING] = { 0,0,0,0,0,0 };	//弱スイカ
		const int MELON_STRENGTH[SETTING] = { 0,0,0,0,0,0 };	//強スイカ
		const int CHERRY_WEAKNESS[SETTING] = { 0,0,0,0,0,0 };	//弱チェリー
		const int CHERRY_STRENGTH[SETTING] = { 0,0,0,0,0,0 };	//強チェリー
	};
}