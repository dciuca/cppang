#pragma once

#include "IEntity.h"
#include "raylib.h"

class Player : public IEntity
{
public:
    Player(float x, float y);
    ~Player() = default;

    // Implementation of pure virtual methods from IEntity
    void SetActive(bool active) override;
    Vector2 GetPosition() override;
    void SetPosition(Vector2 position) override;
    void Update() override;
    void Draw() override;

    // Player-specific methods
    void HandleInput();
    void ClampToScreen(int screenWidth);

private:
    float speed;
    float width;
    float height;
};