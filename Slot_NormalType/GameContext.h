#pragma once
#include "GameScene.h"

class GameContext
{
public:
	static GameContext& Instance()
	{
		static GameContext instance;
		return instance;
	}

	void Init();
	void Update(float deltaTime);

private:
	GameContext() = default;

	GameScene gameScene = {};
};