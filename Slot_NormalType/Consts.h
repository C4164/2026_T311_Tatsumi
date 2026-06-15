#pragma once

namespace Const
{
	//設定の段階(数)
	constexpr int SETTING = 6;

	//設定別の小役確率[分子：16bit(65536)分の何か]
	struct Probability
	{
		const int BELL_1[SETTING] = { 0,0,0,0,0,0 };			//ベル１
		const int BELL_2[SETTING] = { 0,0,0,0,0,0 };			//ベル２
		const int NAVIGATED_BELL[SETTING] = { 0,0,0,0,0,0 };	//押し順ベル
		const int REPLAY_1[SETTING] = { 0,0,0,0,0,0 };			//リプレイ１
		const int REPLAY_2[SETTING] = { 0,0,0,0,0,0 };			//リプレイ２
		const int MELON_WEAKNESS[SETTING] = { 0,0,0,0,0,0 };	//弱スイカ
		const int MELON_STRENGTH[SETTING] = { 0,0,0,0,0,0 };	//強スイカ
		const int CHERRY_WEAKNESS[SETTING] = { 0,0,0,0,0,0 };	//弱チェリー
		const int CHERRY_STRENGTH[SETTING] = { 0,0,0,0,0,0 };	//強チェリー
	};
}