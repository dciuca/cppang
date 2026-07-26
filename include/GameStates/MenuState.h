#pragma once

#include "IGameState.h"

class MenuState : public IGameState
{
public:
    MenuState();
    ~MenuState() override = default;

    void HandleInput() override;
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;
};
