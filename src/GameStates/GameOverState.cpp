#include "GameOverState.h"
#include "raylib.h"

GameOverState::GameOverState()
{
}

void GameOverState::HandleInput()
{
    // Check for restart or exit input
    if (IsKeyPressed(KEY_R))
    {
        RequestStateChange(GameStateRequest::ChangeToPlaying);
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        // TODO: Exit game
    }
}

void GameOverState::Enter()
{
    // Any initialization for game over state
}

void GameOverState::Update()
{
    // Any updates for game over state, if needed
}

void GameOverState::Draw() const
{
    BeginDrawing();
    ClearBackground(RED);

    // Draw GAME OVER text centered
    const char *text = "GAME OVER";
    int fontSize = 60;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int textWidth = MeasureText(text, fontSize);
    int textX = (screenWidth - textWidth) / 2;
    int textY = screenHeight / 2 - 50;

    DrawText(text, textX, textY, fontSize, WHITE);

    // Draw instructions
    const char *instructions = "Press R to restart or ESC to exit";
    int instrSize = 30;
    int instrWidth = MeasureText(instructions, instrSize);
    int instrX = (screenWidth - instrWidth) / 2;
    int instrY = textY + 80;

    DrawText(instructions, instrX, instrY, instrSize, GRAY);

    DrawFPS(10, 10);

    EndDrawing();
}

void GameOverState::Exit()
{
    // Cleanup if needed
}
