#pragma once

#include "GameLevels.h"
#include "Timer.h"

class LevelManager
{
public:
    LevelManager()
        : m_currentLevel(0), m_levelTimer(100, false, false, nullptr), m_score(0), m_lives(MAX_LIVES) {};

    unsigned short GetCurrentLevel() const { return m_currentLevel; };
    void NextLevel()
    {
        m_currentLevel++;
        m_levelTimer.activate();
    };
    void Reset()
    {
        m_currentLevel = 0;
        m_lives = MAX_LIVES;
        m_score = 0;
    };
    unsigned short GetLives() const { return m_lives; };
    unsigned short GetMaxLives() const { return MAX_LIVES; };
    unsigned int GetScore() const { return m_score; };
    void SetLives(unsigned short lives) { m_lives = lives; };
    void SetScore(unsigned int score) { m_score = score; };
    Timer &GetLevelTimer() { return m_levelTimer; };

private:
    static const unsigned short MAX_LIVES = 3;
    unsigned short m_currentLevel;
    unsigned short m_lives;
    unsigned int m_score;
    Timer m_levelTimer;
};
