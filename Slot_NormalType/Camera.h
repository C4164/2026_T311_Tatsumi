#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
public:
    XMFLOAT3 eye = { 0.0f, 0.0f, -5.0f };
    XMFLOAT3 target = { 0.0f, 0.0f,  0.0f };
    XMFLOAT3 up = { 0.0f, 1.0f,  0.0f };

    float fov = XMConvertToRadians(60.0f);
    float aspect = 1.0f;
    float nearZ = 0.1f;
    float farZ = 1000.0f;

    //ViewçsóÒ
    XMMATRIX GetViewMatrix() const
    {
        return XMMatrixLookAtLH(
            XMLoadFloat3(&eye),
            XMLoadFloat3(&target),
            XMLoadFloat3(&up)
        );
    }

    //ProjectionçsóÒ
    XMMATRIX GetProjMatrix() const
    {
        return XMMatrixPerspectiveFovLH(
            fov,
            aspect,
            nearZ,
            farZ
        );
    }

    //ViewProjçsóÒ
    XMMATRIX GetViewProjMatrix() const
    {
        return GetViewMatrix() * GetProjMatrix();
    }
};

