#include "Ball.h"
// #include "Physics.h"
#include "raylib.h"
#include <cmath>

Ball::Ball(
    float x,
    float y,
    float radius,
    float angle,
    Color color)
    : radius(radius), angle(angle), color(color), texture({0}), useTexture(false)
{
    position = {x, y};
    velocity = {0, 0};
    speed = 250.0f;

    // Sets initial velocity from angle, that's all angle ever does
    float angleRad = angle * DEG2RAD;
    velocity.x = speed * cosf(angleRad);
    velocity.y = speed * sinf(angleRad);
}

// void Ball::Update()
// {
// }

void Ball::Draw()
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

void Ball::SetColor(Color newColor)
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

Vector2 Ball::GetDimensions()
{
    return {radius, radius};
}