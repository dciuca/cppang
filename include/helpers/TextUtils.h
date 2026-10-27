#pragma once
#include "raylib.h"
#include <cmath>

inline const char *GetFontPath()
{
    // return "assets/fonts/spicysale.ttf";
    return "assets/fonts/TitanOne-Regular.ttf";
};

struct TextStyle
{
    float size;
    float spacing;
    Color color;
};

namespace TextStyles
{
    inline TextStyle Title() { return {64.0f, 2, YELLOW}; }
    inline TextStyle Subtitle() { return {32.0f, 2, YELLOW}; }
    inline TextStyle HUD() { return {28.0f, 2, YELLOW}; }
}

inline void DrawTextOutlined(const char *text, const Font &font, const TextStyle &style,
                              Vector2 position, float outlineSize = 2.0f,
                              Color outlineColor = BLACK)
{
    for (float dx = -outlineSize; dx <= outlineSize; dx += outlineSize)
    {
        for (float dy = -outlineSize; dy <= outlineSize; dy += outlineSize)
        {
            if (dx == 0.0f && dy == 0.0f)
                continue;
            Vector2 outlinePos = {position.x + dx, position.y + dy};
            DrawTextEx(font, text, outlinePos, style.size, style.spacing, outlineColor);
        }
    }
    DrawTextEx(font, text, position, style.size, style.spacing, style.color);
}

inline void DrawOffsetText(const char *text, const Font &font, const TextStyle &style,
                           float offsetX = 0.0f, float offsetY = 0.0f)
{
    Vector2 position = {offsetX, offsetY};
    DrawTextOutlined(text, font, style, position);
}

inline void DrawCenteredText(const char *text, const Font &font, const TextStyle &style,
                             float offsetY = 0.0f)
{
    Vector2 textSize = MeasureTextEx(font, text, style.size, style.spacing);
    Vector2 position = {
        (GetScreenWidth() - textSize.x) / 2.0f,
        (GetScreenHeight() - textSize.y) / 2.0f + offsetY};
    DrawTextOutlined(text, font, style, position);
}

inline void DrawFadingText(const char *text, const Font &font, const TextStyle &style,
                           float offsetY = 0.0f, float speed = 3.0f)
{
    float time = GetTime();
    float alpha = (sinf(time * speed) + 1.0f) / 2.0f;
    alpha = 0.3f + 0.7f * alpha;

    Color fadedColor = style.color;
    fadedColor.a = (unsigned char)(alpha * 255);

    TextStyle fadedStyle = style;
    fadedStyle.color = fadedColor;

    DrawCenteredText(text, font, fadedStyle, offsetY);
}