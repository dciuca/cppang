#include "GameOverState.h"
#include "TextUtils.h"

GameOverState::GameOverState()
{
}

void GameOverState::HandleInput()
{
    if (IsKeyPressed(KEY_R))
    {
        RequestStateChange(GameStateRequest::ChangeToMenu);
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        RequestStateChange(GameStateRequest::Quit);
    }
}

void GameOverState::Enter()
{
    m_background = LoadTexture("assets/gameover.png");
    m_font = LoadFont(GetFontPath());
}

void GameOverState::Update()
{
}

void GameOverState::Draw() const
{
    BeginDrawing();

    DrawTexture(m_background, 0, 0, WHITE);
    DrawCenteredText("GAME OVER", m_font, TextStyles::Title(), 0.0f);
    DrawFadingText("Press R to restart or ESC to exit", m_font, TextStyles::Subtitle(), 200.0f);

    EndDrawing();
}

void GameOverState::Exit()
{
    UnloadTexture(m_background);
    UnloadFont(m_font);
}
