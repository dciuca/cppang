#pragma once

#include "IEntity.h"

class Obstacle : public IEntity
{
public:
    Obstacle(
        float x,
        float y,
        float width,
        float height,
        Color color);
    ~Obstacle() = default;

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
};