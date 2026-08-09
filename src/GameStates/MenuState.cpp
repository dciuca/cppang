#include "MenuState.h"
#include "raylib.h"

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
}

void MenuState::Update()
{
}

void MenuState::Draw() const
{
    float time = GetTime();
    bool showText = ((int)(time * 2)) % 2 == 0;
    Vector2 position = {210.0f, 480.0f};

    BeginDrawing();

    ClearBackground(DARKBLUE);
    DrawTexture(m_background, 0, 0, WHITE);
    if (showText)
    {
        DrawTextEx(customFont, "Press SPACE to start", position, 32, 2, YELLOW);
    }
    DrawFPS(10, 10); // DEBUG

    EndDrawing();
}

void MenuState::Exit()
{
    UnloadTexture(m_background);
}
