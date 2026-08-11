#pragma once

#include "IEntity.h"
#include "raylib.h"
#include <string>

class Ball : public IEntity
{
public:
    Ball(
        float x,
        float y,
        float radius,
        float angle,
        float speed = 250.0f,
        Color color = WHITE,
        const std::string &texturePath = "");
    ~Ball() = default;

    // Implementation of pure virtual methods from IEntity
    void SetColor(const Color &newColor) override;
    Color GetColor() const { return color; };
    Vector2 GetDimensions() const override;
    ShapeType GetShapeType() const { return ShapeType::CIRCLE; };
    void Update() override;
    void Draw() const override;

private:
    float radius;
    float angle; // in degrees
    Color color;
    std::string m_texturePath;
};
