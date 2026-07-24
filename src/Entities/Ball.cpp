#include "Ball.h"
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
    position = { x, y };
    velocity = { 0, 0 };
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

Vector2 Ball::GetPosition()
{
    return position;
}

void Ball::SetPosition(Vector2 newPosition)
{
    position = newPosition;
}

void Ball::Update()
{
    if (!isActive) return;

    // Update position based on velocity
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();

    // Bounce on screen borders
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Left and right walls
    if (position.x - radius <= 0)
    {
        position.x = radius;
        ReverseX();
    }
    else if (position.x + radius >= screenWidth)
    {
        position.x = screenWidth - radius;
        ReverseX();
    }

    // Top wall
    if (position.y - radius <= 0)
    {
        position.y = radius;
        ReverseY();
    }
    // Bottom wall
    if (position.y + radius >= screenHeight)
    {
        position.y = screenHeight - radius;
        ReverseY();
    }

    // Reset velocity for next frame (optional, depending on your design)
    // velocity = { 0, 0 };
}

void Ball::Draw()
{
    if (!isActive) return;

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

void Ball::SetTexture(const std::string& texturePath)
{
    if (useTexture)
    {
        UnloadTexture(texture);
    }

    texture = LoadTexture(texturePath.c_str());
    useTexture = true;
}

void Ball::ReverseX()
{
    velocity.x = -velocity.x;
}

void Ball::ReverseY()
{
    velocity.y = -velocity.y;
}

bool Ball::IsBelow(float y) const
{
    return position.y - radius > y;
}

float Ball::GetRadius() const
{
    return radius;
}
