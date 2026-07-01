#pragma once
#include <array>
#include "GameObject.h"
#include "Consts.h"

class Reel
{
public:
	Reel() = default;
	~Reel() = default;

	void Init();
	void Update(float deltaTime);

private:
	//入力を検知しリールの停止やリールの始動をする関数
	void ActionCheck();

	//リールを回転させる関数
	void UpdatePosition(
		float deltaTime,
		std::array<GameObject*, Const::REELSYMBOL_NUM> reelObjects,
		bool isSpin,
		bool isStop);

	//リールを停止させる関数
	void ReelStop(
		float deltaTime,
		std::array<GameObject*, Const::REELSYMBOL_NUM> reelObjects,
		bool& isSpin,
		bool isStop);

	//停止形を決定する関数
	//リールを５つごとに分けて、停止形を決定する
	void SetTargetIndex_Left();
	void SetTargetIndex_Center();
	void SetTargetIndex_Right();

	int TargetIndexCalc(int stopIdx, int target);

	void SetStopIndex(std::array<GameObject*, Const::REELSYMBOL_NUM> reelObjects);

	std::array<GameObject*, Const::REELSYMBOL_NUM>leftReelObjects{};
	std::array<GameObject*, Const::REELSYMBOL_NUM>centerReelObjects{};
	std::array<GameObject*, Const::REELSYMBOL_NUM>rightReelObjects{};

	//リールが回転しているかどうか
	bool isSpinLeft = false;
	bool isSpinCenter = false;
	bool isSpinRight = false;

	//停止ボタンが押されているかどうか
	bool isStopLeft = false;
	bool isStopCenter = false;
	bool isStopRight = false;

	//タイマー
	float reelStopTimer = Const::REEL_STOPINTERVAL_TIME;//リール停止から次のリール停止までの時間を管理
	float waitTimer = Const::WAIT_TIME;					//リール始動から次のリール始動までの時間を管理

	//一番下のY座標
	const float down = -Const::SYMBOLDISTANCE_HEIGHT * 18;

	//中段に停止させるオブジェクトの添え字
	int targetIndex = -1;

	//停止ボタンが押されたときの中段位置のオブジェクトの添え字
	int stopIndex = -1;

	Const::MinorPrize minorPrize = Const::MinorPrize::nothing;
};