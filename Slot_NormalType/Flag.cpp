#include "Flag.h"
#include "Random.h"
#include <intrin.h>

void Flag::Init()
{
	Xoroshiro128PP rng;

	//64bitの値を返すクロックカウンタを取得
	uint64_t t = __rdtsc();

	//0x9E3779B97F4A7C15ULLはビット拡散用の定数
	//この値とXORすることでビットパターンの偏りが少なくなる
	rng.seed(t, t ^ 0x9E3779B97F4A7C15ULL);
}

MinorPrize Flag::FlagUp()
{

	MinorPrize mp = Const::bell;

	return mp;
}