#pragma once

class GameContext
{
public:
	static GameContext& Instance()
	{
		static GameContext instance;
		return instance;
	}

	void Update(float deltaTime);

private:
	GameContext() = default;
};