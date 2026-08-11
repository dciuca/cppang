#pragma once

#include "GameLevels.h"

class LevelManager
{
public:
    LevelManager() : m_currentLevel(0) {};

    size_t GetCurrentLevel() const { return m_currentLevel; };
    void NextLevel() { m_currentLevel++; };
    void Reset() { m_currentLevel = 0; };
    size_t GetLives() const { return m_lives; };
    size_t GetScore() const { return m_score; };
    void SetLives(size_t lives) { m_lives = lives; };
    void SetScore(size_t score) { m_score = score; };

private:
    size_t m_currentLevel;
    size_t m_lives;
    size_t m_score;
};
