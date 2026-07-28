#include "Player.h"
// #include "Physics.h"
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

    // Load texture if a path is provided
    if (!texturePath.empty())
    {
        texture = LoadTexture(texturePath.c_str());
        useTexture = true;
    }
}

// void Player::Update()
// {
// }

void Player::Draw()
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

Vector2 Player::GetDimensions()
{
    return {width, height};
}