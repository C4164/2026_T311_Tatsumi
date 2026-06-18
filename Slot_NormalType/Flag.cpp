#include "Flag.h"
#include "Random.h"
#include <intrin.h>

void Flag::Init()
{
	uint64_t r1 = GetHardwareRandom64();
	uint64_t r2 = GetHardwareRandom64();
	rng.seed(r1, r2);
}

//小役をまとめる配列
static constexpr MinorPrize prizeOrder[] =
{
	Const::bell,
	Const::replay,
	Const::chance,
	Const::melon_weakness,
	Const::melon_strength_1,
	Const::melon_strength_2,
	Const::cherry_weakness,
	Const::cherry_strength_1,
	Const::cherry_strength_2,
};

//小役の確率を参照する配列
static const uint16_t* prizeTable[] =
{
	Const::BELL.data(),
	Const::REPLAY.data(),
	Const::CHANCE.data(),
	Const::MELON_WEAKNESS.data(),
	Const::MELON_STRENGTH_1.data(),
	Const::MELON_STRENGTH_2.data(),
	Const::CHERRY_WEAKNESS.data(),
	Const::CHERRY_STRENGTH_1.data(),
	Const::CHERRY_STRENGTH_2.data(),
};

MinorPrize Flag::FlagUp(const int setting)
{
	//16bitの乱数を取得
	uint16_t t = rng.GetRandom16();
	//累積用の変数
	uint16_t sum = 0;

	//小役の確率値を累積していきながら、該当する小役を返す
	for (int i = 0; i < std::size(prizeOrder); i++)
	{
		sum += prizeTable[i][setting];

		if (t < sum)
		{
			currentMP = prizeOrder[i];
			return currentMP;
		}
	}

	//確率に漏れた場合ははずれ
	currentMP = Const::nothing;
	return currentMP;
}