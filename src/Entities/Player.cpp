#include "Player.h"
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

void Player::MoveLeft()
{
    velocity.x = -speed;
    m_animState = AnimState::WalkLeft;
    if (m_currentFrame > 3)
        m_currentFrame = 0;
}

void Player::MoveRight()
{
    velocity.x = speed;
    m_animState = AnimState::WalkRight;
    if (m_currentFrame > 3)
        m_currentFrame = 0;
}

void Player::StopMoving()
{
    velocity.x = 0;
    if (m_animState != AnimState::Shooting)
        m_animState = AnimState::Idle;
}

void Player::StartShooting()
{
    m_animState = AnimState::Shooting;
    m_currentFrame = 4;
}

void Player::Winning()
{
    m_animState = AnimState::Winning;
    m_currentRow = 1;
    m_currentFrame = 7;
}

void Player::Update()
{
    m_animTimer += GetFrameTime();
    if (m_animTimer < 0.1f)
        return;
    m_animTimer = 0.0f;

    switch (m_animState)
    {
    case AnimState::WalkLeft:
    case AnimState::WalkRight:
        m_currentFrame = (m_currentFrame + 1) % 4;
        break;
    case AnimState::Shooting:
        if (m_currentFrame < 5)
            m_currentFrame++;
        else
            m_animState = AnimState::Idle;
        break;
    case AnimState::Idle:
        m_currentFrame = 4;
        break;
    case AnimState::Winning:
        m_currentRow = 1;
        m_currentFrame = 7;
        break;
    }
}

void Player::Draw() const
{
    if (this->IsActive() == false)
        return;

    if (useTexture)
    {
        float mirror = (m_animState == AnimState::WalkRight) ? -1.0f : 1.0f;
        Rectangle source = {
            (float)(m_currentFrame * 32),
            (float)(m_currentRow * 32),
            32.0f * mirror,
            32.0f};
        Rectangle dest = {position.x, position.y, width, height};
        DrawTexturePro(texture, source, dest, {0, 0}, 0.0f, color);
    }
    else
    {
        DrawRectangle(position.x, position.y, width, height, color);
    }
}

void Player::SetColor(const Color &newColor)
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

Vector2 Player::GetDimensions() const
{
    return {width, height};
}