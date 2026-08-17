#pragma once

#include "GameLevels.h"
#include "Timer.h"

class LevelManager
{
public:
    LevelManager() : m_currentLevel(0), m_levelTimer(100, false, false, nullptr) {};

    unsigned short GetCurrentLevel() const { return m_currentLevel; };
    void NextLevel()
    {
        m_currentLevel++;
        m_levelTimer.activate();
    };
    void Reset()
    {
        m_currentLevel = 0;
        m_lives = 3;
        m_score = 0;
    };
    unsigned short GetLives() const { return m_lives; };
    unsigned int GetScore() const { return m_score; };
    void SetLives(unsigned short lives) { m_lives = lives; };
    void SetScore(unsigned short score) { m_score = score; };
    Timer &GetLevelTimer() { return m_levelTimer; };

private:
    unsigned short m_currentLevel;
    unsigned short m_lives;
    unsigned int m_score;
    Timer m_levelTimer;
};
