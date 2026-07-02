#include "ModeSelection.h"

void ModeSelection::Init()
{
	uint64_t r1 = GetHardwareRandom64();
	uint64_t r2 = GetHardwareRandom64();
	rng.seed(r1, r2);
}

void ModeSelection::ResetMode(int setting)
{

}

bool ModeSelection::SetMode(int setting, MinorPrize mp)
{
	if (currentMode == Mode::Bounus) { return true; }
	if (mp == MinorPrize::bell) { return false; }

	//16bitの乱数を取得
	uint16_t t = rng.GetRandom16();

	//リプレイはモード転落抽選
	if(mp == MinorPrize::replay)
	{
		if (t < REPLAY_MODE_DOWN) 
		{
			currentMode = (currentMode == Mode::HighMode) ? Mode::NormalMode : Mode::LowMode;
			return currentMode == Mode::Bounus;
		}
	}

	//累積用の変数
	uint16_t sum = 0;

	MODE_TRANS_RATE modeTransRate;
	if (mp == MinorPrize::cherry_weakness)
	{
		modeTransRate = CHERY_WEAKNESS_TRANS_RATE;
	}

	//モード移行の確率値を累積していきながら、該当するモードセットする
	if (currentMode == Mode::LowMode)
	{
		sum += modeTransRate.LOW_TO_BOUNUS[setting];

		if (t < sum)
		{
			currentMode = Mode::Bounus;
			return currentMode == Mode::Bounus;
		}

		sum += modeTransRate.LOW_TO_HIGH[setting];

		if (t < sum)
		{
			currentMode = Mode::HighMode;
			return currentMode == Mode::Bounus;
		}

		sum += modeTransRate.LOW_TO_NORMAL[setting];

		if (t < sum)
		{
			currentMode = Mode::NormalMode;
			return currentMode == Mode::Bounus;
		}

		return currentMode == Mode::Bounus;
	}
	else if (currentMode == Mode::NormalMode)
	{
		sum += modeTransRate.NORMAL_TO_BOUNUS[setting];

		if (t < sum)
		{
			currentMode = Mode::Bounus;
			return currentMode == Mode::Bounus;
		}

		sum += modeTransRate.NORMAL_TO_HIGH[setting];

		if (t < sum)
		{
			currentMode = Mode::HighMode;
			return currentMode == Mode::Bounus;
		}

		return currentMode == Mode::Bounus;
	}
	else
	{
		sum += modeTransRate.HIGH_TO_BOUNUS[setting];

		if (t < sum)
		{
			currentMode = Mode::Bounus;
			return currentMode == Mode::Bounus;
		}

		return currentMode == Mode::Bounus;
	}

	return false;
}