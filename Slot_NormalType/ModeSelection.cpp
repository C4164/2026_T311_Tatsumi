#include "ModeSelection.h"

void ModeSelection::Init()
{
	uint64_t r1 = GetHardwareRandom64();
	uint64_t r2 = GetHardwareRandom64();
	rng.seed(r1, r2);
}

void ModeSelection::ResetMode()
{
	//16bitの乱数を取得
	uint16_t t = rng.GetRandom16();

	//累積用の変数
	uint16_t sum = 0;

	for (int i = 0; i < 3; i++)
	{
		sum += MODE_RESET_RATE[i];
		if (t < sum)
		{
			currentMode = static_cast<Mode>(i);
			break;
		}
	}
}

void ModeSelection::SetMode(int setting, MinorPrize mp)
{
	if (currentMode == Mode::Bonus) { return; }
	if (mp == MinorPrize::bell) { return; }

	//16bitの乱数を取得
	uint16_t t = rng.GetRandom16();

	//リプレイはモード転落抽選
	if (mp == MinorPrize::replay)
	{
		if (t < REPLAY_MODE_DOWN)
		{
			currentMode = (currentMode == Mode::HighMode) ? Mode::NormalMode : Mode::LowMode;
		}
		return;
	}

	//はずれはボーナス抽選のみ
	if (mp == MinorPrize::nothing)
	{
		if (currentMode == LowMode)
		{
			if (t < BONUS_HIT_LOW_MODE)
			{
				currentMode = Mode::Bonus;
				isReadyBonus = true;
			}
		}
		else if (currentMode == NormalMode)
		{
			if (t < BONUS_HIT_NORMAL_MODE)
			{
				currentMode = Mode::Bonus;
				isReadyBonus = true;
			}
		}
		else if (currentMode == HighMode)
		{
			if (t < BONUS_HIT_HIGH_MODE)
			{
				currentMode = Mode::Bonus;
				isReadyBonus = true;
			}
		}
		return;
	}

	//累積用の変数
	uint16_t sum = 0;

	//モード移行抽選の確率値を取得する
	const MODE_TRANS_RATE* modeTransRate;

	switch (mp)
	{
	case MinorPrize::cherry_weakness:
		modeTransRate = &CHERY_WEAKNESS_TRANS_RATE;
		break;

	case MinorPrize::cherry_strength_1:
	case MinorPrize::cherry_strength_2:
		modeTransRate = &CHERY_STRENGTH_TRANS_RATE;
		break;

	case MinorPrize::melon_weakness:
		modeTransRate = &MELON_WEAKNESS_TRANS_RATE;
		break;

	case MinorPrize::melon_strength_1:
	case MinorPrize::melon_strength_2:
		modeTransRate = &MELON_STRENGTH_TRANS_RATE;
		break;

	case MinorPrize::chance:
		modeTransRate = &CHANCE_TRANS_RATE;
		break;

	default:
		OutputDebugStringA("MinorPrize is Out");
		return;
	}


	//モード移行の確率値を累積していきながら、該当するモードセットする
	//低確モードの場合
	if (currentMode == Mode::LowMode)
	{
		if (TranRateCalc(t, sum, setting, modeTransRate->LOW_TO_BOUNUS, Mode::Bonus))
		{
			return;
		}

		if (TranRateCalc(t, sum, setting, modeTransRate->LOW_TO_HIGH, Mode::HighMode))
		{
			return;
		}

		if (TranRateCalc(t, sum, setting, modeTransRate->LOW_TO_NORMAL, Mode::NormalMode))
		{
			return;
		}

		return;
	}
	//通常モードの場合
	else if (currentMode == Mode::NormalMode)
	{
		if (TranRateCalc(t, sum, setting, modeTransRate->NORMAL_TO_BOUNUS, Mode::Bonus))
		{
			return;
		}

		if (TranRateCalc(t, sum, setting, modeTransRate->NORMAL_TO_HIGH, Mode::HighMode))
		{
			return;
		}

		return;
	}
	//高確モードの場合
	else
	{
		if (TranRateCalc(t, sum, setting, modeTransRate->HIGH_TO_BOUNUS, Mode::Bonus))
		{
			return;
		}

		return;
	}

	return;
}

bool ModeSelection::TranRateCalc(
	uint16_t t,
	uint16_t& sum,
	int setting,
	const std::array<uint16_t, SETTING>& transRate,
	Mode mode)
{
	sum += transRate[setting];
	if (sum == 0) { OutputDebugStringA("sum overNumber"); }
	if (t < sum)
	{
		currentMode = mode;
		if (currentMode == Mode::Bonus)
		{
			isReadyBonus = true;
		}
		return true;
	}

	return false;
}