#include "Ball.h"
#include "GameTypes.h"
#include <cmath>

Ball::Ball(
    float x,
    float y,
    float radius,
    float angle,
    float speed,
    Color color,
    const std::string &texturePath,
    int generation,
    CollectibleType pendingCollectibleType,
    int pendingDropGeneration
)
    : radius(radius), angle(angle), color(color), 
    generation(generation), 
    pendingCollectibleType(pendingCollectibleType), 
    pendingDropGeneration(pendingDropGeneration)
{
    position = {x, y};
    velocity = {0, 0};
    this->speed = speed;

    float angleRad = angle * DEG2RAD;
    velocity.x = speed * cosf(angleRad);
    velocity.y = speed * sinf(angleRad);

    if (!texturePath.empty())
    {
        texture = LoadTexture(texturePath.c_str());
        useTexture = true;
        m_ownsTexture = true;
    }
}

Ball::~Ball()
{
    if (!m_ownsTexture)
        useTexture = false; // prevent IEntity from unloading a handle we don't own
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
        Rectangle source = {0, 0, (float)texture.width, (float)texture.height};
        Rectangle dest = {position.x - radius, position.y - radius, radius * 2, radius * 2};
        DrawTexturePro(texture, source, dest, {0, 0}, 0.0f, color);
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

Vector2 Ball::GetDimensions() const
{
    return {radius, radius};
}