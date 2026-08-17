#pragma once

#include "IGameState.h"
#include "LevelManager.h"

class LevelCompleteState : public IGameState
{
public:
    LevelCompleteState(LevelManager &levelManager, Texture2D levelGhost);
    ~LevelCompleteState() override = default;

    void HandleInput() override;
    void Enter() override;
    void Update() override;
    void Draw() const override;
    void Exit() override;

private:
    unsigned short m_level;
    Texture2D m_levelGhost{};
    bool m_hasGhost = false;
    Font m_font;
};