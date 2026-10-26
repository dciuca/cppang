#include "Collectible.h"
#include "GameTypes.h"

Collectible::Collectible(
    float x,
    float y,
    CollectibleType type,
    float radius,
    float speed,
    Color color,
    const std::string &texturePath)
    : type(type), radius(radius), color(color)
{
    position = {x, y};
    velocity = {0, 0};
    this->speed = speed;

    if (!texturePath.empty())
    {
        texture = LoadTexture(texturePath.c_str());
        useTexture = true;
    }
}

void Collectible::Update()
{
}

void Collectible::Draw() const
{
    if (this->IsActive() == false)
        return;

    if (useTexture)
    {
        Rectangle source = {0, 0, (float)texture.width, (float)texture.height};
        Rectangle dest = {position.x - radius, position.y - radius, radius * 2, radius * 2};
        DrawTexturePro(texture, source, dest, {0, 0}, 0.0f, color);
    }
    else
    {
        DrawCircle(position.x, position.y, radius, color);
    }
}

void Collectible::SetColor(const Color &newColor)
{
    color = newColor;
}

Vector2 Collectible::GetDimensions() const
{
    return {radius, radius};
}