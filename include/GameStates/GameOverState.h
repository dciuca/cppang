#pragma once

#include "IGameState.h"
#include "raylib.h"

class GameOverState : public IGameState
{
public:
    GameOverState();
    ~GameOverState() override = default;

    void HandleInput() override;
    void Enter() override;
    void Update() override;
    void Draw() const override;
    void Exit() override;

private:
    Texture2D m_background;
};
