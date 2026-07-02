#pragma once
#include "Consts.h"

class CoinManager
{
public:
	static CoinManager& Instance()
	{
		static CoinManager instance;
		return instance;
	}

	void AddCoin(int amount)
	{
		coinCount += amount;
		if (coinCount > Const::COIN_MAX)
		{
			coinCount = Const::COIN_MAX;
		}
	}

	void RemoveCoin(int amount)
	{
		coinCount -= amount;
		if (coinCount < Const::COIN_MIN)
		{
			coinCount = Const::COIN_MIN;
		}
	}

	void CoinPayout(
		int leftIndex,
		int centerIndex,
		int rightIndex
	);

	int GetCoinCount()const { return coinCount; }

private:
	CoinManager() = default;
	~CoinManager() = default;

	int coinCount = 0;
};