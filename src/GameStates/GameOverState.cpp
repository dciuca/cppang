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
    m_background = LoadTexture("assets/gameover.png");
}

void GameOverState::Update()
{
    // Any updates for game over state, if needed
}

void GameOverState::Draw() const
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(m_background, 0, 0, WHITE);

    // Draw GAME OVER text centered
    const char *text = "GAME OVER";
    int fontSize = 80;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int textWidth = MeasureText(text, fontSize);
    int textX = (screenWidth - textWidth) / 2;

    DrawText(text, textX, 400, fontSize, WHITE);

    // Draw instructions
    const char *instructions = "Press R to restart or ESC to exit";
    int instrSize = 30;
    int instrWidth = MeasureText(instructions, instrSize);
    int instrX = (screenWidth - instrWidth) / 2;

    DrawText(instructions, instrX, 480, instrSize, RED);

    DrawFPS(10, 10);

    EndDrawing();
}

void GameOverState::Exit()
{
    UnloadTexture(m_background);
}
