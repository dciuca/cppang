#pragma once

#include "GameLevels.h"

class LevelManager
{
public:
    LevelManager() : m_currentLevel(0) {};

    size_t GetCurrentLevel() const { return m_currentLevel; };
    void NextLevel() { m_currentLevel++; };
    void Reset() { m_currentLevel = 0; };
    bool HasNextLevel() const { return m_currentLevel < GameLevels::MAX_LEVELS; };

private:
    size_t m_currentLevel;
};
