#include "Flag.h"

void Flag::Init()
{
	uint64_t r1 = GetHardwareRandom64();
	uint64_t r2 = GetHardwareRandom64();
	rng.seed(r1, r2);
}

MinorPrize Flag::FlagUp()
{
	MinorPrize mp = bell_1;

	uint16_t t = rng.GetRandom16();

	return mp;
}