#include "PauseState.h"
#include "raylib.h"

PauseState::PauseState()
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
    float time = GetTime();
    bool showText = ((int)(time * 2)) % 2 == 0;
    Vector2 position = {210.0f, 280.0f};

    BeginDrawing();

    if (showText)
    {
        DrawTextEx(customFont, "Press SPACE to resume", position, 32, 2, YELLOW);
    }
    DrawFPS(10, 10);

    EndDrawing();
}

void PauseState::Exit()
{
}
