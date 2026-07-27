#include "Player.h"
#include "Physics.h"
#include "raylib.h"

Player::Player(
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
    isActive = true;

    // Load texture if a path is provided
    if (!texturePath.empty())
    {
        texture = LoadTexture(texturePath.c_str());
        useTexture = true;
    }
}

void Player::SetActive(bool active)
{
    isActive = active;
}

void Player::Update()
{
    if (!isActive)
        return;

    // Update position based on velocity
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();

    Physics::BounceOnX(*this, width);

    // Reset velocity for next frame
    velocity = {0, 0};
}

void Player::Draw()
{
    if (!isActive)
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

void Player::SetColor(Color newColor)
{
    color = newColor;
}

void Player::SetTexture(const std::string &texturePath)
{
    if (useTexture)
    {
        UnloadTexture(texture);
    }

    texture = LoadTexture(texturePath.c_str());
    useTexture = true;
}