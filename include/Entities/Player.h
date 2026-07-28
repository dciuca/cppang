#pragma once

#include <string>
#include "IEntity.h"
#include "raylib.h"

class Player : public IEntity
{
public:
    Player(
        float x = 400.0f,
        float y = 550.0f,
        float width = 20.0f,
        float height = 50.0f,
        Color color = BLUE,
        const std::string &texturePath = "");
    ~Player() = default;

    // Implementation of pure virtual methods from IEntity
    void SetColor(Color newColor) override;
    void SetTexture(const std::string &texturePath) override;
    Vector2 GetDimensions() override;
    void Update() override;
    void Draw() override;

private:
    float width;
    float height;
    Color color;
    Texture2D texture;
    bool useTexture;
};