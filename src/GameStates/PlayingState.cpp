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

        // Player position
        Vector2 velocity = p1->velocity;
        if (IsKeyDown(KEY_LEFT))
            velocity.x = -p1->speed;
        else if (IsKeyDown(KEY_RIGHT))
            velocity.x = p1->speed;
        p1->velocity = velocity;

        // Player shoot
        if (IsKeyPressed(KEY_SPACE))
        {
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
    // Init player1
    auto p1 = std::make_unique<Player>();
    m_players.push_back(p1.get());       // observe raw pointer before moving
    m_entities.push_back(std::move(p1)); // transfer ownership

    LoadObstacles(this->m_level);
    LoadLevelBalls(this->m_level);

    for (auto &entity : m_entities)
    {
        entity->SetActive(true);
    }
}

void PlayingState::Update()
{
    // Physics Update
    for (auto &player : m_players)
    {
        Physics::UpdateCharacter(*player);
    }
    for (auto &ball : m_balls)
    {
        Physics::UpdateBall(*ball);
    }
    for (auto &harpoon : m_harpoons)
    {
        harpoon->Update();
    }

    // Ball-Player Collision Detection
    m_ballsToSplit.clear();
    for (auto &ball : m_balls)
    {
        for (auto &player : m_players)
        {
            if (Physics::CheckCircleRectCollision(*ball, *player))
            {
                RequestStateChange(GameStateRequest::ChangeToGameOver);
                return;
            }
        }

        // Ball-Harpoon Collision Detection
        for (auto &harpoon : m_harpoons)
        {
            if (Physics::CheckAndResolveCircleRectCollision(*ball, *harpoon))
            {
                harpoon->SetActive(false);
                m_ballsToSplit.push_back(ball);
            }
        }

        // Ball-Obstacle Collision Detection
        for (auto &obstacle : m_obstacles)
        {
            Physics::CheckAndResolveCircleRectCollision(*ball, *obstacle);
        }
    }

    // Harpoon-Obstacle Collision Detection
    for (auto &harpoon : m_harpoons)
    {
        for (auto &obstacle : m_obstacles)
        {
            if (Physics::CheckCircleRectCollision(*harpoon, *obstacle))
            {
                harpoon->SetActive(false);
            }
        }
    }

    if (m_ballsToSplit.size() > 0)
        SplitBalls(m_ballsToSplit);

    // DEBUG
    // Print the size of m_entities, m_balls and m_ballsToSplit every second
    // static float timeAccumulator = 0.0f;
    // timeAccumulator += GetFrameTime();
    // if (timeAccumulator >= 1.0f)
    // {
        // timeAccumulator = 0.0f;
    //     std::cout << "Entities: " << m_entities.size() << ", Balls: " << m_balls.size() << ", BallsToSplit: " << m_ballsToSplit.size() << std::endl;
}

void PlayingState::SplitBalls(std::vector<Ball *> m_ballsToSplit)
{
    for (auto &ball : m_ballsToSplit)
    {
        // Create two smaller balls
        float newRadius = ball->GetDimensions().x / 2.0f; // Assuming GetDimensions().x returns diameter
        if (newRadius > 10.0f)                            // Minimum size check
        {
            auto ball1 = std::make_unique<Ball>(
                ball->position.x - newRadius,
                ball->position.y,
                newRadius,
                45.0f,
                RED);
            auto ball2 = std::make_unique<Ball>(
                ball->position.x + newRadius,
                ball->position.y,
                newRadius,
                135.0f,
                BLUE);

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
            config.x, config.y, config.radius, config.angle, config.color);
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
            config.x, config.y, config.width, config.height, config.color);
        m_obstacles.push_back(obstacle.get());
        m_entities.push_back(std::move(obstacle));
    }
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
    removeInactive(m_players);

    m_entities.erase(
        std::remove_if(m_entities.begin(), m_entities.end(),
                       [](const std::unique_ptr<IEntity> &e)
                       { return !e->IsActive(); }),
        m_entities.end());

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

    for (const auto &entity : m_entities)
    {
        entity->Draw();
    }

    DrawFPS(10, 10);

    EndDrawing();
}

void PlayingState::Exit()
{
    m_entities.clear();
}