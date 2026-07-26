#include "GameLoop.h"
#include "PlayingState.h"
#include "GameOverState.h"
#include "raylib.h"

GameLoop::GameLoop()
{
	// Initialize the game with a default state, e.g., PlayingState
	ChangeState(std::make_unique<PlayingState>());
}

void GameLoop::Run() {
    while (!WindowShouldClose()) {
        if (currentState) {
            currentState->HandleInput();
            currentState->Update();
            currentState->Draw();
        }
    }
}

void GameLoop::ChangeState(std::unique_ptr<IGameState> newState) {
    // Exit current state if it exists
    if (currentState) {
        currentState->Exit();
    }

    // Change to new state
    currentState = std::move(newState);

    // Enter new state if it exists
    if (currentState) {
        currentState->Enter();
    }
}