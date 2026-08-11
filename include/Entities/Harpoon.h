#pragma once

#include <string>
#include "IEntity.h"
#include "raylib.h"

class Harpoon : public IEntity
{
public:
    Harpoon(
        float x,
        float y,
        float width = 3.0f,
        float height = 0.0f,
        Color color = PURPLE,
        const std::string &texturePath = "");
    ~Harpoon() = default;

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
    float m_time = 0.0f;
    float m_spawnY;
};