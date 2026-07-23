#pragma once
#include <memory>
#include "IGameState.h"

class GameLoop
{
public:
	GameLoop();
	~GameLoop() = default;

	void Run();

private:
	std::unique_ptr<IGameState> currentState;
	void ChangeState(std::unique_ptr<IGameState> newState);
};