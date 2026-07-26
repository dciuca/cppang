#pragma once

#include "IGameState.h"

class GameOverState : public IGameState
{
public:
    GameOverState();
    ~GameOverState() override = default;

    void HandleInput() override;
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;
};
