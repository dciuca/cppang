#pragma once

#include "IGameState.h"

class LevelCompleteState : public IGameState
{
public:
    LevelCompleteState(size_t level, Texture2D levelGhost);
    ~LevelCompleteState() override = default;

    void HandleInput() override;
    void Enter() override;
    void Update() override;
    void Draw() const override;
    void Exit() override;

private:
    size_t m_level;
    Texture2D m_levelGhost{};
    bool m_hasGhost = false;
};