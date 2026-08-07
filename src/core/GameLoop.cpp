#include "GameLoop.h"
#include "MenuState.h"
#include "PlayingState.h"
#include "GameOverState.h"
#include "PauseState.h"
#include "raylib.h"

GameLoop::GameLoop()
{
    // Initialize the game with a default state
    ChangeState(std::make_unique<MenuState>());
}

void GameLoop::Run()
{
    while (!WindowShouldClose())
    {

        if (currentState)
        {

            currentState->HandleInput();
            currentState->Update();
            currentState->Cleanup();

            switch (currentState->GetGameStateRequest())
            {
            case GameStateRequest::ChangeToPlaying:
                m_levelManager.Reset();
                ChangeState(std::make_unique<PlayingState>(m_levelManager.GetCurrentLevel()));
                break;

            case GameStateRequest::ChangeToNextLevel:
                m_levelManager.NextLevel();
                ChangeState(std::make_unique<PlayingState>(m_levelManager.GetCurrentLevel()));
                break;

            case GameStateRequest::ChangeToGameOver:
                m_levelManager.Reset();
                ChangeState(std::make_unique<GameOverState>());
                break;

            case GameStateRequest::PauseGame:
                previousState = std::move(currentState);
                ChangeState(std::make_unique<PauseState>());
                break;

            case GameStateRequest::ResumeGame:
                if (previousState)
                {
                    currentState = std::move(previousState);
                }
                break;
            }

            currentState->Draw();
        }
    }
}

void GameLoop::ChangeState(std::unique_ptr<IGameState> newState)
{
    // Exit current state if it exists
    if (currentState)
    {
        currentState->Exit();
    }

    // Change to new state
    currentState = std::move(newState);

    // Enter new state if it exists
    if (currentState)
    {
        currentState->Enter();
    }
}