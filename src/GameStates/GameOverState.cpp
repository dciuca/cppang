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
    float time = GetTime();
    bool showText = ((int)(time * 2)) % 2 == 0;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(m_background, 0, 0, WHITE);

    DrawTextEx(customFont, "GAME OVER", (Vector2){200, 280}, 80, 2, RED);
    if (showText)
        DrawTextEx(customFont, "Press R to restart or ESC to exit", (Vector2){135, 400}, 32, 2, YELLOW);

    DrawFPS(10, 10);

    EndDrawing();
}

void GameOverState::Exit()
{
    UnloadTexture(m_background);
}
