#include "PauseState.h"
#include "raylib.h"

PauseState::PauseState(size_t level, Texture2D levelGhost)
    : m_level(level), m_levelGhost(levelGhost), m_hasGhost(levelGhost.id != 0)
{
}

void PauseState::HandleInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        gameStateRequest = GameStateRequest::ResumeGame;
    }
}

void PauseState::Enter()
{
    gameStateRequest = GameStateRequest::None;
}

void PauseState::Update()
{
}

void PauseState::Draw() const
{
    BeginDrawing();

    ClearBackground(BLACK);

    if (m_hasGhost)
    {
        DrawTexturePro(
            m_levelGhost,
            {0, 0, (float)m_levelGhost.width, (float)m_levelGhost.height},
            {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
            {0, 0},
            0.0f,
            Fade(WHITE, 0.5f));
    }

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.45f));

    float time = GetTime();
    bool showText = ((int)(time * 2)) % 2 == 0;

    Vector2 positionFixedText = {290.0f, 200.0f};
    Vector2 positionFlashingText = {220.0f, 380.0f};

    const char *levelText = TextFormat("LEVEL %d", m_level);

    DrawTextEx(customFont, levelText, positionFixedText, 64, 2, YELLOW);
    if (showText)
    {
        DrawTextEx(customFont, "Press SPACE to play", positionFlashingText, 32, 2, YELLOW);
    }

    EndDrawing();
}

void PauseState::Exit()
{
    if (m_hasGhost)
    {
        UnloadTexture(m_levelGhost);
    }
}