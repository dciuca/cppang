#include "LevelCompleteState.h"
#include "TextUtils.h"

LevelCompleteState::LevelCompleteState(LevelManager &levelManager, Texture2D levelGhost)
    : m_level(levelManager.GetCurrentLevel()), m_levelGhost(levelGhost), m_hasGhost(levelGhost.id != 0)
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
    m_font = LoadFont(GetFontPath());
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

    DrawCenteredText(TextFormat("LEVEL %d COMPLETE!", m_level), m_font, TextStyles::Title(), 0.0f);
    DrawFadingText("Press SPACE to start", m_font, TextStyles::Subtitle(), 200.0f);

    EndDrawing();
}

void LevelCompleteState::Exit()
{
    if (m_hasGhost)
    {
        UnloadTexture(m_levelGhost);
    }
    UnloadFont(m_font);
}