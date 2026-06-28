#pragma once
#include "GameObject.h"

class ObjectFactory {
public:
	static GameObject* CreateObject(
		const std::wstring& path,
		const XMFLOAT3& pos,
		const XMFLOAT3& scale
	);
};