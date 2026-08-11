#include "MenuState.h"
#include "TextUtils.h"

MenuState::MenuState()
{
}

void MenuState::HandleInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        RequestStateChange(GameStateRequest::ChangeToNextLevel);
    }
    else if (IsKeyPressed(KEY_ESCAPE))
    {
        RequestStateChange(GameStateRequest::Quit);
    }
}

void MenuState::Enter()
{
    gameStateRequest = GameStateRequest::None;
    m_background = LoadTexture("assets/menu.png");
    m_font = LoadFont(GetFontPath());
}

void MenuState::Update()
{
}

void MenuState::Draw() const
{
    BeginDrawing();

    ClearBackground(DARKBLUE);
    DrawTexture(m_background, 0, 0, WHITE);
    DrawFadingText("Press SPACE to start", m_font, TextStyles::Subtitle(), 200.0f);

    DrawFPS(10, 10); // DEBUG

    EndDrawing();
}

void MenuState::Exit()
{
    UnloadTexture(m_background);
    UnloadFont(m_font);
}
