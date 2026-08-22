#include "PlayingState.h"
#include "LevelManager.h"
#include "GameLoop.h"
#include "raylib.h"
#include <iostream>

int main(int argc, char *argv[])
{
    int level = 1;
    if (argc > 1)
        level = std::atoi(argv[1]);

    InitWindow(800, 600, "cppang - level test");
    SetTargetFPS(60);

    LevelManager levelManager;
    levelManager.Reset();

    // Advance to the requested level (m_currentLevel is 0-based, levels are 1-based)
    for (int i = 0; i < level; i++)
        levelManager.NextLevel();

    auto state = std::make_unique<PlayingState>(levelManager);
    state->Enter();

    while (!WindowShouldClose())
    {
        switch (state->GetGameStateRequest())
        {
        case GameStateRequest::PauseGame:
        {
            levelManager.GetLevelTimer().pause();
            // resume immediately — no pause UI in test mode
            levelManager.GetLevelTimer().resume();
            break;
        }
        case GameStateRequest::ChangeToGameOver:
            std::cout << "Game Over at level " << level << "\n";
            goto done;
        case GameStateRequest::ChangeToLevelComplete:
            std::cout << "Level " << level << " completed!\n";
            goto done;
        default:
            break;
        }

        state->HandleInput();
        state->Update();
        state->Draw();
    }

done:
    state->Exit();
    CloseWindow();
}
