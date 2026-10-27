#include "Harpoon.h"
#include <cmath>

Harpoon::Harpoon(
    float x,
    float y,
    float width,
    float height,
    float speed,
    Color color,
    const std::string &texturePath,
    const std::string &arrowTexturePath) : width(width), height(height), speed(speed), color(color)
{
    position = {x, y};
    velocity = {0, 0};
    m_spawnY = y;

    // Load rope texture if a path is provided
    if (!texturePath.empty())
    {
        texture = LoadTexture(texturePath.c_str());
        useTexture = true;
    }

    // Load arrow (tip) texture if a path is provided
    if (!arrowTexturePath.empty())
    {
        m_arrowTexture = LoadTexture(arrowTexturePath.c_str());
        m_useArrowTexture = true;
    }
}

Harpoon::~Harpoon()
{
    if (m_useArrowTexture)
        UnloadTexture(m_arrowTexture);
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

    const float ropeWidth = width * 0.5f;
    const float ropeX = position.x + (width - ropeWidth) * 0.5f;

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
            Rectangle dst = {ropeX, drawY, ropeWidth, clipH};
            DrawTexturePro(texture, src, dst, {0, 0}, 0.0f, color);
        }
    }
    else
    {
        DrawRectangle(ropeX, position.y, ropeWidth, height, color);
    }

    if (m_useArrowTexture)
    {
        float arrowScale = ropeWidth / (float)m_arrowTexture.width;
        float arrowW = ropeWidth;
        float arrowH = (float)m_arrowTexture.height * arrowScale;
        Rectangle src = {0, 0, (float)m_arrowTexture.width, (float)m_arrowTexture.height};
        Rectangle dst = {ropeX, position.y - arrowH, arrowW, arrowH};
        DrawTexturePro(m_arrowTexture, src, dst, {0, 0}, 0.0f, color);
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