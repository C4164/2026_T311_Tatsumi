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

	void Init();

	void ResetMode(int setting);

	bool SetMode(int setting,MinorPrize mp);

private:
	Xoroshiro128PP rng;
	Mode currentMode = Mode::None;
};