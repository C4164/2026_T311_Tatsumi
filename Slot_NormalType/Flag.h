#pragma once

//小役の種類
enum MinorPrize
{
	bell,			//ベル
	replay,			//リプレイ
	chance,			//チャンス目
	melon_weakness,	//弱スイカ
	melon_strength,	//強スイカ
	cherry_weakness,//弱チェリー
	cherry_strength,//強チェリー
};

class Flag 
{
public:
	Flag() = default;

	void Init();		//初期化する関数

	MinorPrize FlagUp();	//フラグを抽選する関数

	//アクセサ
	//現在の小役を取得する関数
	MinorPrize GetCurrentMP()const { return currentMP; }	

private:
	MinorPrize currentMP;	//現在の小役

	
};