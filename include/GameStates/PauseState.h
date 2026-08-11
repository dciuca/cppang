#pragma once

#include "IGameState.h"

class PauseState : public IGameState
{
public:
    PauseState(size_t level, Texture2D levelGhost);
    ~PauseState() override = default;

    void HandleInput() override;
    void Enter() override;
    void Update() override;
    void Draw() const override;
    void Exit() override;

private:
    size_t m_level;
    Texture2D m_levelGhost{};
    bool m_hasGhost = false;
    Font m_font;
};