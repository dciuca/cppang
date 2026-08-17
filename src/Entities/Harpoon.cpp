#include "Harpoon.h"
#include <cmath>

Harpoon::Harpoon(
    float x,
    float y,
    float width,
    float height,
    Color color,
    const std::string &texturePath) : width(width), height(height), color(color)
{
    position = {x, y};
    velocity = {0, 0};
    speed = 1000.0f;
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

    // if (useTexture)
    // {
    //     DrawTexture(texture, position.x, position.y, color);
    // }
    // else
    // {
    //     DrawRectangle(position.x, position.y, width, height, color);
    // }

    Vector2 basePos = {position.x, m_spawnY};
    Vector2 tipPos = position;

    float dx = tipPos.x - basePos.x;
    float dy = tipPos.y - basePos.y;
    float length = sqrtf(dx * dx + dy * dy);

    if (length > 1.0f)
    {
        Vector2 norm = {dx / length, dy / length};
        Vector2 perp = {-norm.y, norm.x};

        int segments = 120;
        for (int i = 0; i < segments; i++)
        {
            float t1 = (float)i / segments;
            float t2 = (float)(i + 1) / segments;

            Vector2 p1 = {
                basePos.x + norm.x * (t1 * length),
                basePos.y + norm.y * (t1 * length)};
            Vector2 p2 = {
                basePos.x + norm.x * (t2 * length),
                basePos.y + norm.y * (t2 * length)};

            float wave = sinf(m_time * 3.0f + t1 * 14.0f) * 6.0f * t1;
            p1.x += perp.x * wave;
            p1.y += perp.y * wave;

            float wave2 = sinf(m_time * 3.0f + t2 * 5.0f) * 3.0f * t2;
            p2.x += perp.x * wave2;
            p2.y += perp.y * wave2;

            DrawLineEx(p1, p2, 2.5f, RED);
        }
    }

    // Harpoon arrow
    DrawCircleV(position, 8.0f, PURPLE); // External
    DrawCircleV(position, 5.0f, WHITE);  // Internal (light)
    DrawCircleV(position, 2.0f, RED);    // Centre

    if (useTexture)
    {
        DrawTexture(texture, position.x, position.y, color);
    }
    else
    {
        DrawCircleV(position, 6.0f, color);
        DrawCircleV(position, 3.0f, YELLOW);
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