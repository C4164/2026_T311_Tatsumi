#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Transform
{
public:
    XMFLOAT3 position = { 0.0f, 0.0f, 0.0f };
    XMFLOAT3 rotation = { 0.0f, 0.0f, 0.0f };
    XMFLOAT3 scale = { 1.0f, 1.0f, 1.0f };

    //ワールド行列を返す
    XMMATRIX GetMatrix() const
    {
        //大きさ
        XMMATRIX S = XMMatrixScaling(scale.x, scale.y, scale.z);

        //回転
        XMMATRIX R =
            XMMatrixRotationX(rotation.x) *
            XMMatrixRotationY(rotation.y) *
            XMMatrixRotationZ(rotation.z);

        //平行移動
        XMMATRIX T = XMMatrixTranslation(position.x, position.y, position.z);

        //S・R・Tの順で掛ける
        return S * R * T;
    }
};

