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
        bool isFixed,
        float speed,
        Color color = WHITE,
        const std::string &texturePath = "");
    ~Obstacle() = default;

    // Implementation of pure virtual methods from IEntity
    void SetColor(const Color &newColor) override;
    Vector2 GetDimensions() const override;
    ShapeType GetShapeType() const override { return ShapeType::RECTANGLE; };
    void Update() override;
    void Draw() const override;
    bool IsFixed() const { return isFixed; }

private:
    float width;
    float height;
    bool isFixed;
    float speed;
    Color color;
};