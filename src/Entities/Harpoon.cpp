#include "Harpoon.h"
#include "raylib.h"

Harpoon::Harpoon(
    float x,
    float y,
    float width,
    float height,
    Color color,
    const std::string &texturePath) : width(width), height(height), color(color), texture({0}), useTexture(false)
{
    position = {x, y};
    velocity = {0, 0};
    speed = 300.0f;

    // Load texture if a path is provided
    if (!texturePath.empty())
    {
        texture = LoadTexture(texturePath.c_str());
        useTexture = true;
    }
}

void Harpoon::Update()
{
    float growth = speed * GetFrameTime();
    position.y -= growth; // top edge moves up
    height += growth;     // height grows to keep bottom fixed

    if (position.y <= 0)
    {
        position.y = 0;
        SetActive(false);
    }
}

void Harpoon::Draw() const
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

void Harpoon::SetColor(const Color &newColor)
{
    color = newColor;
}

void Harpoon::SetTexture(const std::string &texturePath)
{
    if (useTexture)
    {
        UnloadTexture(texture);
    }

    texture = LoadTexture(texturePath.c_str());
    useTexture = true;
}

Vector2 Harpoon::GetDimensions() const
{
    return {width, height};
}