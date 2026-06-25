#pragma once
#include <vector>
#include "GameObject.h"

class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    //シーン開始時に一度だけ呼ばれる
    virtual void Init() = 0;

    //毎フレーム更新
    virtual void Update(float deltaTime) {}

    //毎フレーム描画）
    virtual void Render() {}

    //シーン終了時に呼ばれる
    virtual void End() {}

protected:
    std::vector<GameObject*> objects;

    void AddObject(GameObject* obj)
    {
        objects.push_back(obj);
    }
};

