#pragma once

#include "IEntity.h"
#include "raylib.h"
#include "GameTypes.h"
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
        const std::string &texturePath = "",
        int generation = 1,
        CollectibleType pendingCollectibleType = CollectibleType::None,
        int pendingDropGeneration = 0
    );
    ~Ball();

    // Implementation of pure virtual methods from IEntity
    void SetColor(const Color &newColor) override;
    Color GetColor() const { return color; };
    Vector2 GetDimensions() const override;
    ShapeType GetShapeType() const override { return ShapeType::CIRCLE; };
    void Update() override;
    void Draw() const override;
    int GetGeneration() const { return generation; };
    CollectibleType GetPendingCollectibleType() const { return pendingCollectibleType; };
    int GetPendingDropGeneration() const { return pendingDropGeneration; };

private:
    float radius;
    float angle; // in degrees
    Color color;
    int generation;
    CollectibleType pendingCollectibleType;
    int pendingDropGeneration;
    bool m_ownsTexture = false;

};
