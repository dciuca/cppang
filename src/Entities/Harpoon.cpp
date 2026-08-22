#include "Harpoon.h"
#include <cmath>

Harpoon::Harpoon(
    float x,
    float y,
    float width,
    float height,
    float speed,
    Color color,
    const std::string &texturePath) : width(width), height(height), speed(speed), color(color)
{
    position = {x, y};
    velocity = {0, 0};
    m_spawnY = y;

    // Load texture if a path is provided
    if (!texturePath.empty())
    {
        texture = LoadTexture(texturePath.c_str());
        useTexture = true;
    }
}

void Harpoon::Update()
{
    const float dt = GetFrameTime();
    float growth = speed * dt;
    position.y -= growth;
    height += growth;
    m_time += dt;

    if (position.y <= 0)
    {
        position.y = 0;
        SetActive(false);
    }
}

void Harpoon::Draw() const
{
    if (this->IsActive() == false)
        return;

    if (useTexture)
    {
        float tileH = (float)texture.height;
        for (float y = m_spawnY; y > position.y; y -= tileH)
        {
            float drawY = y - tileH;
            float clipH = tileH;
            if (drawY < position.y)
            {
                clipH = tileH - (position.y - drawY);
                drawY = position.y;
            }
            Rectangle src = {0, tileH - clipH, (float)texture.width, (float)texture.height};
            Rectangle dst = {position.x, drawY, width, clipH};
            DrawTexturePro(texture, src, dst, {0, 0}, 0.0f, color);
        }
    }
    else
    {
        DrawRectangle(position.x, position.y, width, height, color);
    }
}

void Harpoon::SetColor(const Color &newColor)
{
    color = newColor;
}

Vector2 Harpoon::GetDimensions() const
{
    return {width, height};
}