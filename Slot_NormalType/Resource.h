#pragma once
#include <string>

namespace Resource
{
	//Symbols
	static const std::wstring blankPath = L"Data/Texture/blank.png";
	static const std::wstring bellPath = L"Data/Texture/bell.png";
	static const std::wstring replayPath = L"Data/Texture/replay.png";
	static const std::wstring melonPath = L"Data/Texture/melon.png";
	static const std::wstring cherryPath = L"Data/Texture/cherry.png";
	static const std::wstring bonusPath = L"Data/Texture/seven_1.png";
	static const std::wstring bar_whitePath = L"Data/Texture/bar_white.png";
	static const std::wstring bar_blackPath = L"Data/Texture/bar_black.png";

	//Number
	static const std::wstring zeroPath = L"Data/Texture/zero.png";
	static const std::wstring onePath = L"Data/Texture/one.png";
	static const std::wstring twoPath = L"Data/Texture/two.png";
	static const std::wstring threePath = L"Data/Texture/three.png";
	static const std::wstring fourPath = L"Data/Texture/four.png";
	static const std::wstring fivePath = L"Data/Texture/five.png";
	static const std::wstring sixPath = L"Data/Texture/six.png";
	static const std::wstring sevenPath = L"Data/Texture/seven.png";
	static const std::wstring eightPath = L"Data/Texture/eight.png";
	static const std::wstring ninePath = L"Data/Texture/nine.png";

	static const std::wstring minusPath = L"Data/Texture/minus.png";

	//Characters
	static const std::wstring ptPath = L"Data/Texture/pt.png";

	//Color
	static const std::wstring whitePath = L"Data/Texture/white.png";

	//ChanceLamp
	static const std::wstring chance_offPath = L"Data/Texture/chance_off.png";
	static const std::wstring chance_onPath = L"Data/Texture/chance_on.png";

	static const std::array<const std::wstring, Const::REELSYMBOL_NUM> SymbolPaths =
	{
		Resource::blankPath,
		Resource::bellPath,
		Resource::replayPath,
		Resource::melonPath,
		Resource::cherryPath,
		Resource::bonusPath,
		Resource::bar_whitePath,
		Resource::bar_blackPath,
	};

	static const std::array<const std::wstring, 10> NumberPaths =
	{
		Resource::zeroPath,
		Resource::onePath,
		Resource::twoPath,
		Resource::threePath,
		Resource::fourPath,
		Resource::fivePath,
		Resource::sixPath,
		Resource::sevenPath,
		Resource::eightPath,
		Resource::ninePath,
	};
}