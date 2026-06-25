#pragma once
#include "Scene.h"
#include "Mesh.h"
#include "Material.h"
#include "Render.h"
#include "TextureSRV.h"

class GameScene : public Scene
{
public:
    GameScene() = default;
    ~GameScene() override = default;

    void Init() override;
    void Update(float deltaTime) override;
    void Render() override;
    void End() override;
};


