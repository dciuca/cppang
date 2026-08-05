#pragma once

#include <string>
#include "IEntity.h"
#include "raylib.h"

class Player : public IEntity
{
public:
    Player(
        float x = 400.0f,
        float y = 600.0f - 64.0f - BORDER_OFFSET,
        float width = 64.0f,
        float height = 64.0f,
        Color color = WHITE,
        const std::string &texturePath = "");
    ~Player() = default;

    void MoveLeft();
    void MoveRight();
    void StopMoving();
    void StartShooting();

    // Implementation of pure virtual methods from IEntity
    void SetColor(const Color &newColor) override;
    void SetTexture(const std::string &texturePath) override;
    Vector2 GetDimensions() const override;
    ShapeType GetShapeType() const { return ShapeType::RECTANGLE; };
    void Update() override;
    void Draw() const override;

private:
    float width;
    float height;
    Color color;
    Texture2D texture;
    bool useTexture;

    enum class AnimState
    {
        Idle,
        WalkLeft,
        WalkRight,
        Shooting
    };
    AnimState m_animState = AnimState::Idle;
    int m_currentFrame = 4;
    int m_currentRow = 0;
    float m_animTimer = 0.0f;
};