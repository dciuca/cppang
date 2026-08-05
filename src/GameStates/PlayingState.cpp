#include "PlayingState.h"
#include "Player.h"
#include "Ball.h"
#include "Obstacle.h"
#include "GameLevels.h"
#include "raylib.h"
#include <algorithm>

#include <iostream> // DEBUG

PlayingState::PlayingState(size_t level)
    : m_level(level)
{
}

void PlayingState::HandleInput()
{
    // Input Handling for Player 1 (position [0])
    if (m_players.size() > 0 && m_players[0]->IsActive())
    {
        Player *p1 = m_players[0];

        // Player movement
        if (IsKeyDown(KEY_LEFT))
            p1->MoveLeft();
        else if (IsKeyDown(KEY_RIGHT))
            p1->MoveRight();
        else
            p1->StopMoving();

        // Player shoot
        if (IsKeyPressed(KEY_SPACE))
        {
            p1->StartShooting();
            // add new harpoon in m_harpoons & m_entities
            auto harpoon = std::make_unique<Harpoon>(
                p1->position.x + p1->GetDimensions().x / 2.0f,
                p1->position.y);
            harpoon->SetActive(true);
            m_harpoons.push_back(harpoon.get());
            m_entities.push_back(std::move(harpoon));
        }
    }
}

void PlayingState::Enter()
{
    auto bgConfig = GameLevels::GetLevelBackground(m_level);
    m_background = LoadTexture(bgConfig.texturePath.c_str());
    m_backgroundRect = bgConfig.sourceRect;

    // Init player1
    auto p1 = std::make_unique<Player>();
    m_players.push_back(p1.get());
    m_entities.push_back(std::move(p1));
    m_players[0]->SetTexture("assets/player.png");

    LoadObstacles(this->m_level);
    LoadLevelBalls(this->m_level);

    for (auto &entity : m_entities)
    {
        entity->SetActive(true);
    }
}

void PlayingState::Update()
{
    UpdateEntities();
    if (!HandleCollisions())
        return;
    if (!m_ballsToSplit.empty())
        SplitBalls(m_ballsToSplit);
}

void PlayingState::Cleanup()
{
    auto removeInactive = [](auto &vec)
    {
        vec.erase(
            std::remove_if(vec.begin(), vec.end(),
                           [](auto *e)
                           { return !e->IsActive(); }),
            vec.end());
    };

    removeInactive(m_harpoons);
    removeInactive(m_balls);
    // removeInactive(m_players);
    // removeInactive(m_obstacles);

    // m_entities.erase(
    //     std::remove_if(m_entities.begin(), m_entities.end(),
    //                    [](const std::unique_ptr<IEntity> &e)
    //                    { return !e->IsActive(); }),
    //     m_entities.end());

    // Level complete check — runs after inactive entities are removed
    if (m_balls.size() == 0)
    {
        RequestStateChange(GameStateRequest::ChangeToNextLevel);
    }
}

void PlayingState::Draw() const
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexturePro(m_background,
                   m_backgroundRect,
                   {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                   {0, 0}, 0.0f, WHITE);

    for (const auto &entity : m_entities)
    {
        entity->Draw();
    }

    DrawFPS(10, 10);

    EndDrawing();
}

void PlayingState::Exit()
{
    UnloadTexture(m_background);
    m_entities.clear();
}

// private methods
void PlayingState::UpdateEntities()
{
    for (auto &player : m_players)
    {
        Physics::UpdateCharacter(*player);
        player->Update();
    }
    for (auto &ball : m_balls)
        Physics::UpdateBall(*ball);
    for (auto &harpoon : m_harpoons)
        harpoon->Update();
    for (auto &obstacle : m_obstacles)
        if (!obstacle->IsFixed())
            Physics::UpdateObstacle(*obstacle);
}

bool PlayingState::HandleCollisions()
{
    m_ballsToSplit.clear();
    for (auto &ball : m_balls)
    {
        for (auto &player : m_players)
        {
            if (Physics::CheckCircleRectCollision(*ball, *player))
            {
                RequestStateChange(GameStateRequest::ChangeToGameOver);
                return false;
            }
        }

        for (auto &harpoon : m_harpoons)
        {
            if (!harpoon->IsActive())
                continue;
            if (Physics::CheckAndResolveCircleRectCollision(*ball, *harpoon))
            {
                harpoon->SetActive(false);
                m_ballsToSplit.push_back(ball);
            }
        }

        for (auto &obstacle : m_obstacles)
            Physics::CheckAndResolveCircleRectCollision(*ball, *obstacle);
    }

    for (auto &harpoon : m_harpoons)
    {
        if (!harpoon->IsActive())
            continue;
        for (auto &obstacle : m_obstacles)
        {
            if (Physics::CheckRectRectCollision(*harpoon, *obstacle))
                harpoon->SetActive(false);
        }
    }

    return true;
}

void PlayingState::SplitBalls(const std::vector<Ball *> &m_ballsToSplit)
{
    for (auto &ball : m_ballsToSplit)
    {
        // Create two smaller balls
        float newRadius = ball->GetDimensions().x / 2.0f;
        if (newRadius > 10.0f) // Minimum size check
        {
            auto ball1 = std::make_unique<Ball>(
                ball->position.x - newRadius,
                ball->position.y,
                newRadius,
                45.0f,
                ball->speed,
                ball->GetColor());
            auto ball2 = std::make_unique<Ball>(
                ball->position.x + newRadius,
                ball->position.y,
                newRadius,
                135.0f,
                ball->speed,
                ball->GetColor());

            if (!ball->GetTexturePath().empty())
            {
                ball1->SetTexture(ball->GetTexturePath());
                ball2->SetTexture(ball->GetTexturePath());
            }

            ball1->SetActive(true);
            ball2->SetActive(true);
            m_balls.push_back(ball1.get());
            m_entities.push_back(std::move(ball1));

            m_balls.push_back(ball2.get());
            m_entities.push_back(std::move(ball2));
        }
        ball->SetActive(false); // Deactivate the original ball
    }
}

void PlayingState::LoadLevelBalls(size_t level)
{
    m_balls.clear();
    auto balls = GameLevels::GetLevelBalls(level);
    for (const auto &config : balls)
    {
        auto ball = std::make_unique<Ball>(
            config.x, config.y, config.radius, config.angle, config.speed, config.color);
        if (!config.texturePath.empty())
            ball->SetTexture(config.texturePath);
        m_balls.push_back(ball.get());
        m_entities.push_back(std::move(ball));
    }
}

void PlayingState::LoadObstacles(size_t level)
{
    auto obstacles = GameLevels::GetLevelObstacles(level);
    for (const auto &config : obstacles)
    {
        auto obstacle = std::make_unique<Obstacle>(
            config.x, config.y, config.width, config.height, config.isFixed, config.color);
        m_obstacles.push_back(obstacle.get());
        m_entities.push_back(std::move(obstacle));
    }
}
