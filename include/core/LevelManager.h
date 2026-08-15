#pragma once

#include "GameLevels.h"
#include "Timer.h"

class LevelManager
{
public:
    LevelManager() : m_currentLevel(0), m_levelTimer(100, false, true, nullptr) {};

    size_t GetCurrentLevel() const { return m_currentLevel; };
    void NextLevel() { m_currentLevel++; m_levelTimer.activate(); };
    void Reset()
    {
        m_currentLevel = 0;
        m_lives = 3;
        m_score = 0;
        m_levelTimer.activate();
    };
    size_t GetLives() const { return m_lives; };
    size_t GetScore() const { return m_score; };
    void SetLives(size_t lives) { m_lives = lives; };
    void SetScore(size_t score) { m_score = score; };
    Timer &GetLevelTimer() { return m_levelTimer; };

private:
    size_t m_currentLevel;
    size_t m_lives;
    size_t m_score;
    Timer m_levelTimer;
};
