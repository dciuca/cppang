#include "Obstacle.h"

Obstacle::Obstacle(
    float x,
    float y,
    float width,
    float height,
    Color color)
    : width(width), height(height), color(color), texture({0}), useTexture(false)
{
    position = {x, y};
    velocity = {0, 0};
    speed = 250.0f;
}

void Obstacle::Update()
{
}

void Obstacle::Draw() const
{
    if (this->IsActive() == false)
        return;

    if (useTexture)
    {
        DrawTexture(texture, position.x, position.y, color);
    }
    else
    {
        DrawRectangle(position.x, position.y, width, height, color);
    }
}

void Obstacle::SetColor(const Color &newColor)
{
    color = newColor;
}

void Obstacle::SetTexture(const std::string &texturePath)
{
    if (useTexture)
    {
        UnloadTexture(texture);
    }

    texture = LoadTexture(texturePath.c_str());
    useTexture = true;
}

Vector2 Obstacle::GetDimensions() const
{
    return {width, height};
}