#include "PauseState.h"
#include "raylib.h"

PauseState::PauseState(size_t level)
    : m_level(level)
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
    Vector2 positionFixedText = {310.0f, 70.0f};
    Vector2 positionFlashingText = {220.0f, 280.0f};
    const char *levelText = "LEVEL %d\n";
    levelText = TextFormat(levelText, m_level);

    BeginDrawing();

    DrawTextEx(customFont, levelText, positionFixedText, 64, 2, YELLOW);
    if (showText)
    {
        DrawTextEx(customFont, "Press SPACE to play", positionFlashingText, 32, 2, YELLOW);
    }

    EndDrawing();
}

void PauseState::Exit()
{
}
