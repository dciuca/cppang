#include "MenuState.h"
#include "raylib.h"

MenuState::MenuState()
{
}

void MenuState::HandleInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        RequestStateChange(GameStateRequest::ChangeToPlaying);
    }
    else if (IsKeyPressed(KEY_ESCAPE))
    {
        RequestStateChange(GameStateRequest::Quit);
    }
}

void MenuState::Enter()
{
    gameStateRequest = GameStateRequest::None;
    m_background = LoadTexture("assets/cover.png");
}

void MenuState::Update()
{
    // Any updates for menu state, if needed
}

void MenuState::Draw() const
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawTexture(m_background, 0, 0, WHITE);
    DrawFPS(10, 10);

    EndDrawing();
}

void MenuState::Exit()
{
    UnloadTexture(m_background);
}
