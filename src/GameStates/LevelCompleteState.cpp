#include "LevelCompleteState.h"
#include "raylib.h"

LevelCompleteState::LevelCompleteState(size_t level, Texture2D levelGhost)
    : m_level(level), m_levelGhost(levelGhost), m_hasGhost(levelGhost.id != 0)
{
}

void LevelCompleteState::HandleInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        gameStateRequest = GameStateRequest::ChangeToNextLevel;
    }
}

void LevelCompleteState::Enter()
{
    gameStateRequest = GameStateRequest::None;
}

void LevelCompleteState::Update()
{
}

void LevelCompleteState::Draw() const
{
    BeginDrawing();

    ClearBackground(WHITE);

    if (m_hasGhost)
    {
        DrawTexturePro(
            m_levelGhost,
            {0, 0, (float)m_levelGhost.width, (float)m_levelGhost.height},
            {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
            {0, 0},
            0.0f,
            WHITE);
    }

    float time = GetTime();
    bool showText = ((int)(time * 2)) % 2 == 0;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    const char *levelText = TextFormat("LEVEL %d COMPLETE!", m_level);

    Vector2 textSize = MeasureTextEx(customFont, levelText, 64, 2);
    Vector2 positionFixedText = {
        (screenWidth - textSize.x) / 2.0f,
        (screenHeight - textSize.y) / 2.0f - 50.0f};

    Vector2 flashingTextSize = MeasureTextEx(customFont, "Press SPACE to play", 32, 2);
    Vector2 positionFlashingText = {
        (screenWidth - flashingTextSize.x) / 2.0f,
        (screenHeight - flashingTextSize.y) / 2.0f + 100.0f // Leggermente più in basso
    };

    DrawTextEx(customFont, levelText, positionFixedText, 64, 2, YELLOW);

    if (showText)
    {
        DrawTextEx(customFont, "Press SPACE to play", positionFlashingText, 32, 2, YELLOW);
    }

    EndDrawing();
}

void LevelCompleteState::Exit()
{
    if (m_hasGhost)
    {
        UnloadTexture(m_levelGhost);
    }
}