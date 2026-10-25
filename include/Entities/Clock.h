#pragma once

#include "ICollectible.h"
#include "raylib.h"
#include <string>

class Clock : public ICollectible
{
public:
    Clock(
        float x,
        float y,
        float radius = 10.0f,
        float speed = 0.0f,
        Color color = WHITE,
        const std::string &texturePath = "assets/clock.png");
    ~Clock() = default;

    // Implementation of pure virtual methods from IEntity
    void SetColor(const Color &newColor) override;
    Color GetColor() const { return color; };
    Vector2 GetDimensions() const override;
    ShapeType GetShapeType() const override { return ShapeType::CIRCLE; };
    void Update() override;
    void Draw() const override;
    CollectibleType GetCollectibleType() const override;

private:
    float radius;
    Color color;
};
