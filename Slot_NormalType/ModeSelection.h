#pragma once
#include "Consts.h"
#include "Random.h"

using namespace Const;

class ModeSelection
{
public:
	static ModeSelection& Instance()
	{
		static ModeSelection instance;
		return instance;
	}

	//初期化関数
	void Init();

	//モードをリセットする関数
	void ResetMode();

	//モード移行を行う関数
	void SetMode(int setting, MinorPrize mp);

	bool IsReadyBonus() const { return isReadyBonus; }
	void SetReadyBonus(bool readyBonus) { isReadyBonus = readyBonus; }

	bool IsBonusTime() const { return isBonusTime; }
	void SetBonusTime(bool bonusTime) { isBonusTime = bonusTime; }

	Mode GetMode()const { return currentMode; }

	void AddPayOutNum(int num = Const::BELL_PAYOUT)
	{
		payOutNum += num;
		if (payOutNum >= 285)
		{
			payOutNum = 0;
			isBonusTime = false;
			ResetMode();
		}
	}

private:
	//モード移行の確率を計算し、確率に該当するかどうかの判定を行う
	bool TranRateCalc(
		uint16_t t,
		uint16_t& sum,
		int setting,
		const std::array<uint16_t, SETTING>& transRate,
		Mode mode);

	Xoroshiro128PP rng;
	Mode currentMode = Mode::None;

	bool isReadyBonus = false;
	bool isBonusTime = false;

	int payOutNum = 0;
};