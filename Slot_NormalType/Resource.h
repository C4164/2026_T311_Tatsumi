#pragma once
#include <string>

namespace Resource
{
	static const std::wstring blankPath = L"Data/Texture/blank.png";
	static const std::wstring bellPath = L"Data/Texture/bell.png";
	static const std::wstring replayPath = L"Data/Texture/replay.png";
	static const std::wstring melonPath = L"Data/Texture/melon.png";
	static const std::wstring cherryPath = L"Data/Texture/cherry.png";
	static const std::wstring sevenPath = L"Data/Texture/seven.png";
	static const std::wstring bar_whitePath = L"Data/Texture/bar_white.png";
	static const std::wstring bar_blackPath = L"Data/Texture/bar_black.png";

	static const std::wstring whitePath = L"Data/Texture/white.png";

	static const std::array<const std::wstring, Const::REELSYMBOL_NUM> SymbolPaths =
	{
		Resource::blankPath,
		Resource::bellPath,
		Resource::replayPath,
		Resource::melonPath,
		Resource::cherryPath,
		Resource::sevenPath,
		Resource::bar_whitePath,
		Resource::bar_blackPath,
	};
}