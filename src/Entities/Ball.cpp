#include "Ball.h"
#include "Physics.h"
#include "raylib.h"
#include <cmath>

Ball::Ball(
    float x,
    float y,
    float radius,
    float speed,
    float angle,
    Color color)
    : radius(radius), speed(speed), angle(angle), color(color), texture({0}), useTexture(false)
{
    position = {x, y};
    velocity = {0, 0};
    isActive = true;

    // Calculate velocity components based on angle
    float angleRad = angle * DEG2RAD;
    velocity.x = speed * cosf(angleRad);
    velocity.y = speed * sinf(angleRad);
}

void Ball::SetActive(bool active)
{
    isActive = active;
}

void Ball::Update()
{
    if (!isActive)
        return;

    // Update position based on velocity
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();

    Physics::BounceOnXY(*this, radius);
}

void Ball::Draw()
{
    if (!isActive)
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
