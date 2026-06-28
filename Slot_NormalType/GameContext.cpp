#include "GameContext.h"

void GameContext::Init() 
{
	gameScene.Init();
}

void GameContext::Update(float deltaTime)
{
	gameScene.Update(deltaTime);
}