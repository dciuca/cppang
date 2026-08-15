#pragma once

#include <string>
#include "IEntity.h"
#include "Timer.h"
#include "raylib.h"

class Player : public IEntity
{
public:
    Player(
        float x,
        float y,
        float width,
        float height,
        Color color,
        const std::string &texturePath = "");
    ~Player() = default;

    void MoveLeft();
    void MoveRight();
    void StopMoving();
    void StartShooting();
    void Winning();
    void ActivateInvincibility();
    bool IsInvincible() const;

    // Implementation of pure virtual methods from IEntity
    void SetColor(const Color &newColor) override;
    Vector2 GetDimensions() const override;
    ShapeType GetShapeType() const { return ShapeType::RECTANGLE; };
    void Update() override;
    void Draw() const override;

private:
    float width;
    float height;
    Color color;

    enum class AnimState
    {
        Idle,
        WalkLeft,
        WalkRight,
        Shooting,
        Winning
    };
    AnimState m_animState = AnimState::Idle;
    int m_currentFrame = 4;
    int m_currentRow = 0;
    float m_animTimer = 0.0f;
    Timer m_invincibilityTimer;
};