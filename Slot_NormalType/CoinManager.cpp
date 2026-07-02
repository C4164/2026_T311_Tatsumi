#include "CoinManager.h"

void CoinManager::CoinPayout(
	int leftIndex,
	int centerIndex,
	int rightIndex
)
{
	using namespace Const;

	//ベルの払い出し条件
	if (
		leftIndex % SLIDE_SYMBOL_MAX == 4 &&
		centerIndex % SLIDE_SYMBOL_MAX == 0 &&
		rightIndex % SLIDE_SYMBOL_MAX == 2
		)
	{
		AddCoin(BELL_PAYOUT);
	}
	//リプレイの払い出し条件
	else if (
		leftIndex % SLIDE_SYMBOL_MAX == 4 &&
		centerIndex % SLIDE_SYMBOL_MAX == 2 &&
		rightIndex % SLIDE_SYMBOL_MAX == 1
		)
	{
		AddCoin(REPLAY_PAYOUT);
	}
	//弱スイカの払い出し条件
	else if (
		leftIndex % SLIDE_SYMBOL_MAX == 0 &&
		(centerIndex == 14 || centerIndex == 19) &&
		(rightIndex == 6 || rightIndex == 11)
		)
	{
		AddCoin(MELON_PAYOUT);
	}
	//強スイカの払い出し条件
	else if (
		leftIndex % SLIDE_SYMBOL_MAX == 1 &&
		(centerIndex == 0 || centerIndex == 19) &&
		(rightIndex == 7 || rightIndex == 12)
		)
	{
		AddCoin(MELON_PAYOUT);
	}
	//弱チェリー、強チェリーの払い出し条件
	else if (
		rightIndex % SLIDE_SYMBOL_MAX == 4
		)
	{
		AddCoin(CHERY_PAYOUT);
	}
	//はずれ、小役こぼしの払い出し
	else 
	{
		AddCoin(MISS_PAYOUT);
	}
}