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
            currentState->Update();
            currentState->Draw();
        }

        // Simple frame rate limiting
        // In a more complex implementation, you might want to add
        // proper frame timing and fixed timestep updates
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