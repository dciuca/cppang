#pragma once
#include "raylib.h"
#include <cmath>

inline const char *GetFontPath()
{
    return "assets/fonts/spicysale.ttf";
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
}

inline void DrawCenteredText(const char *text, const Font &font, const TextStyle &style,
                             float offsetY = 0.0f)
{
    Vector2 textSize = MeasureTextEx(font, text, style.size, style.spacing);
    Vector2 position = {
        (GetScreenWidth() - textSize.x) / 2.0f,
        (GetScreenHeight() - textSize.y) / 2.0f + offsetY};
    DrawTextEx(font, text, position, style.size, style.spacing, style.color);
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