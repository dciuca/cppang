#pragma once

#include "GameTypes.h"
#include "ICollectible.h"
#include "raylib.h"
#include <string>

class Collectible : public ICollectible
{
public:
    Collectible(
        float x,
        float y,
        CollectibleType type,
        float radius = 15.0f,
        float speed = 0.0f,
        Color color = WHITE,
        const std::string &texturePath = "");
    ~Collectible() = default;

    // Implementation of pure virtual methods from IEntity
    void SetColor(const Color &newColor) override;
    Color GetColor() const { return color; };
    Vector2 GetDimensions() const override;
    ShapeType GetShapeType() const override { return ShapeType::CIRCLE; };
    void Update() override;
    void Draw() const override;
    CollectibleType GetCollectibleType() const override { return type; };

private:
    CollectibleType type;
    float radius;
    Color color;
};
