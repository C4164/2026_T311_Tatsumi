#pragma once
#include "Scene.h"
#include "Consts.h"

class GameScene : public Scene
{
public:
    GameScene() = default;
    ~GameScene() override = default;

    void Init() override;
    void Update(float deltaTime) override;

private:
    std::array<GameObject*, Const::REELSYMBOL_NUM>leftReelObjects;
    std::array<GameObject*, Const::REELSYMBOL_NUM>centerReelObjects;
    std::array<GameObject*, Const::REELSYMBOL_NUM>rightReelObjects;
};


