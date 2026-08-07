#pragma once

#include "IGameState.h"

class PauseState : public IGameState
{
public:
    PauseState();
    ~PauseState() override = default;

    void HandleInput() override;
    void Enter() override;
    void Update() override;
    void Draw() const override;
    void Exit() override;
};
