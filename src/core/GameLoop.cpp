#include "GameLoop.h"
#include "MenuState.h"
#include "LevelCompleteState.h"
#include "PlayingState.h"
#include "GameOverState.h"
#include "PauseState.h"
#include "raylib.h"

GameLoop::GameLoop()
{
    m_levelManager.Reset();
    m_levelManager.SetLives(3);
    m_levelManager.SetScore(0);
    ChangeState(std::make_unique<MenuState>());
}

void GameLoop::Run()
{
    while (!WindowShouldClose())
    {
        if (currentState)
        {
            switch (currentState->GetGameStateRequest())
            {
            case GameStateRequest::None:
                break;

            case GameStateRequest::ChangeToMenu:
                m_levelManager.Reset();
                ChangeState(std::make_unique<MenuState>());
                break;

            case GameStateRequest::ChangeToLevelComplete:
            {
                Image frame = LoadImageFromScreen();
                Texture2D ghost = LoadTextureFromImage(frame);
                UnloadImage(frame);

                ChangeState(std::make_unique<LevelCompleteState>(m_levelManager.GetCurrentLevel(), ghost));
                break;
            }

            case GameStateRequest::ChangeToNextLevel:
                m_levelManager.NextLevel();
                ChangeState(std::make_unique<PlayingState>(m_levelManager.GetCurrentLevel()));
                break;

            case GameStateRequest::ChangeToGameOver:
                m_levelManager.Reset();
                ChangeState(std::make_unique<GameOverState>());
                break;

            case GameStateRequest::PauseGame:
            {
                Image frame = LoadImageFromScreen();
                Texture2D ghost = LoadTextureFromImage(frame);
                UnloadImage(frame);

                previousState = std::move(currentState);
                ChangeState(std::make_unique<PauseState>(m_levelManager.GetCurrentLevel(), ghost));
                break;
            }

            case GameStateRequest::ResumeGame:
                if (previousState)
                {
                    currentState = std::move(previousState);
                    currentState->Enter();
                }
                break;
            }

            currentState->HandleInput();
            currentState->Update();
            currentState->Draw();
        }
    }
}

void GameLoop::ChangeState(std::unique_ptr<IGameState> newState)
{
    if (currentState)
    {
        currentState->Exit();
    }

    currentState = std::move(newState);

    if (currentState)
    {
        currentState->Enter();
    }
}