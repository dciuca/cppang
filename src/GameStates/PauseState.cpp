#include "PauseState.h"
#include "raylib.h"
#include "TextUtils.h"

PauseState::PauseState(size_t level, Texture2D levelGhost)
    : m_level(level), m_levelGhost(levelGhost), m_hasGhost(levelGhost.id != 0), m_font(LoadFont(GetFontPath()))
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

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.45f)); // Black Fade
    DrawCenteredText(TextFormat("LEVEL %d", m_level), m_font, TextStyles::Title(), 0.0f);
    DrawFadingText("Press SPACE to start", m_font, TextStyles::Subtitle(), 200.0f);

    EndDrawing();
}

void PauseState::Exit()
{
    if (m_hasGhost)
    {
        UnloadTexture(m_levelGhost);
    }
    UnloadFont(m_font);
}