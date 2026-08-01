#include "PlayingState.h"
#include "Player.h"
#include "Ball.h"
#include "GameLevels.h"
#include "raylib.h"
#include <algorithm>

PlayingState::PlayingState()
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

    // // TESTING LEVEL 0 -----------------------------------------------------
    // auto ball1 = std::make_unique<Ball>();
    // m_balls.push_back(ball1.get());
    // m_entities.push_back(std::move(ball1));

    // // add a second ball for testing
    // auto ball2 = std::make_unique<Ball>(200.0f, 200.0f, 30.0f, 60.0f, GREEN);
    // m_balls.push_back(ball2.get());
    // m_entities.push_back(std::move(ball2));
    // ---------------------------------------------------------------------
    auto balls = GameLevels::GetLevelBalls(0);
    for (const auto &config : balls)
    {
        auto ball = std::make_unique<Ball>(
            config.x, config.y, config.radius, config.angle, config.color);
        m_balls.push_back(ball.get());
        m_entities.push_back(std::move(ball));
    }

    // Set Active all the m_entities
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

        // Harpoon-Ball Collision Detection
        for (auto &harpoon : m_harpoons)
        {
            if (Physics::CheckCircleRectCollision(*ball, *harpoon))
            {
                harpoon->SetActive(false);
                ball->SetActive(false); // temporary ball disappears
            }
        }
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