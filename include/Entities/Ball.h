#pragma once

#include "IEntity.h"
#include "raylib.h"
#include <string>

class Ball : public IEntity
{
public:
    Ball(
        float x = 400.0f,
        float y = 300.0f,
        float radius = 60.0f,
        float angle = 45.0f,
        Color color = RED);
    ~Ball() = default;

    // Implementation of pure virtual methods from IEntity
    void SetColor(const Color &newColor) override;
    void SetTexture(const std::string &texturePath) override;
    Vector2 GetDimensions() const override;
    ShapeType GetShapeType() const { return ShapeType::CIRCLE; };
    // void Update() override;
    void Draw() const override;

private:
    float radius;
    float angle; // in degrees
    Color color;
    Texture2D texture;
    bool useTexture;
};
