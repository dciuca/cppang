#include "IGameState.h"
#include "IEntity.h"
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
    PlayingState(size_t level);
    ~PlayingState() override = default;

    void HandleInput() override;
    void Enter() override;
    void Update() override;
    void Cleanup() override;
    void Draw() const override;
    void Exit() override;

private:
    void UpdatePhysics();
    bool HandleCollisions();
    void SplitBalls(const std::vector<Ball *> &ballsToSplit);
    void LoadLevelBalls(size_t level);
    void LoadObstacles(size_t level);

private:
    size_t m_level;
    std::vector<std::unique_ptr<IEntity>> m_entities; // All entities in the game
    std::vector<Player *> m_players;                  // m_entities observer
    std::vector<Ball *> m_balls;                      // m_entities observer
    std::vector<Harpoon *> m_harpoons;                // m_entities observer
    std::vector<Obstacle *> m_obstacles;              // m_entities observer
    std::vector<Ball *> m_ballsToSplit;               // Balls that need to be split
};