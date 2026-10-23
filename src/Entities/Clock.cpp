#include "Clock.h"
#include "GameTypes.h"

Clock::Clock(
    float x,
    float y,
    float radius,
    float speed,
    Color color,
    const std::string &texturePath)
    : radius(radius), color(color)
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

void Clock::Update()
{
}

void Clock::Draw() const
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

void Clock::SetColor(const Color &newColor)
{
    color = newColor;
}

Vector2 Clock::GetDimensions() const
{
    return {radius, radius};
}

CollectibleType Clock::GetCollectibleType() const
{
    return CollectibleType::Clock;
}