#pragma once
#include "Scene.h"
#include "Reel.h"
#include "UI.h"

class GameScene : public Scene
{
public:
	//ƒVƒ“ƒOƒ‹ƒgƒ“
	static GameScene& Instance()
	{
		static GameScene instance;
		return instance;
	}

	void Init() override;
	void Update(float deltaTime) override;
	void DrawObjects(ID3D12GraphicsCommandList* commandList) override;
	void DrawUI(ID3D12GraphicsCommandList* commandList) override;

private:
	GameScene() = default;
	~GameScene() = default;

	Reel reel;

	D3D12_RECT reelScissor = {};
	D3D12_RECT fullScissor = {};

	int setting = 4;
};


