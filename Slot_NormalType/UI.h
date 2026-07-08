#pragma once
#include <array>
#include "GameObject.h"

class UI
{
public:
	static UI& Instance()
	{
		static UI instance;
		return instance;
	}

	void Init();

	void Draw(ID3D12GraphicsCommandList* commandList)const;

	void SetChanceLampOnOff(bool onoff) { chanceLampOn = onoff; }

private:
	UI() = default;
	~UI() = default;

	std::array<GameObject*, 8>gridLines;

	std::array<GameObject*, 10>numbers_ones;
	std::array<GameObject*, 10>numbers_tens;
	std::array<GameObject*, 10>numbers_hundreds;
	std::array<GameObject*, 10>numbers_thousands;
	GameObject* minus;
	GameObject* pt;

	GameObject* chanceLamp_off;
	GameObject* chanceLamp_on;

	float lineWidth = 0.1f;

	bool chanceLampOn = false;
};