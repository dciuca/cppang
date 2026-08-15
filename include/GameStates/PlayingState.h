#pragma once
#include "IGameState.h"
#include "IEntity.h"
#include "LevelManager.h"
#include "Physics.h"
#include "Player.h"
#include "Ball.h"
#include "Obstacle.h"
#include "Harpoon.h"
#include <memory>
#include <vector>

class PlayingState : public IGameState
{
public:
    PlayingState(LevelManager &levelManager);
    ~PlayingState() override = default;

    void HandleInput() override;
    void Enter() override;
    void Update() override;
    void Draw() const override;
    void Exit() override;

private:
    void UpdateEntities();
    bool HandleCollisions();
    void SplitBalls(const std::vector<Ball *> &ballsToSplit);
    void LoadLevelBackground(size_t level);
    void LoadLifebar();
    void LoadPlayers();
    void LoadLevelBalls(size_t level);
    void LoadObstacles(size_t level);
    void LoadHarpoon(Player *p);
    void PauseGame();
    void Cleanup();
    void CheckWinCondition();
    void CheckGameOver();

private:
    LevelManager &m_levelManager;
    Texture2D m_background, m_lifebar;
    Font m_font;
    Rectangle m_backgroundRect, m_lifebarRect;
    bool m_waitingForReady;
    std::vector<std::unique_ptr<IEntity>> m_entities; // All entities in the game
    std::vector<Player *> m_players;                  // m_entities observer
    std::vector<Ball *> m_balls;                      // m_entities observer
    std::vector<Harpoon *> m_harpoons;                // m_entities observer
    std::vector<Obstacle *> m_obstacles;              // m_entities observer
    std::vector<Ball *> m_ballsToSplit;               // Balls that need to be split
};