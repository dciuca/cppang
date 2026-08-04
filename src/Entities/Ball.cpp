#include "Ball.h"
#include "raylib.h"
#include <cmath>

Ball::Ball(
    float x,
    float y,
    float radius,
    float angle,
    Color color,
    const std::string &texturePath)
    : radius(radius), angle(angle), color(color), texture({0}), useTexture(false)
{
    position = {x, y};
    velocity = {0, 0};
    speed = 250.0f;

    float angleRad = angle * DEG2RAD;
    velocity.x = speed * cosf(angleRad);
    velocity.y = speed * sinf(angleRad);

    if (!texturePath.empty())
    {
        texture = LoadTexture(texturePath.c_str());
        useTexture = true;
    }
}

void Ball::Update()
{
}

void Ball::Draw() const
{
    if (this->IsActive() == false)
        return;

    if (useTexture)
    {
        DrawTextureEx(texture, position, 0.0f, 1.0f, color);
    }
    else
    {
        DrawCircle(position.x, position.y, radius, color);
    }
}

void Ball::SetColor(const Color &newColor)
{
    color = newColor;
}

void Ball::SetTexture(const std::string &texturePath)
{
    if (useTexture)
    {
        UnloadTexture(texture);
    }

    texture = LoadTexture(texturePath.c_str());
    useTexture = true;
}

Vector2 Ball::GetDimensions() const
{
    return {radius, radius};
}