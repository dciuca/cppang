#include "PlayingState.h"
#include "Player.h"
#include "Ball.h"
#include "raylib.h"

PlayingState::PlayingState()
{
}

void PlayingState::HandleInput()
{
    // Input Handling for Player 1 (position [0])
    if (m_players.size() > 0 && m_players[0]->IsActive())
    {
        Player *p1 = m_players[0];
        Vector2 velocity = p1->velocity;

        if (IsKeyDown(KEY_LEFT))
            velocity.x = -p1->speed;
        else if (IsKeyDown(KEY_RIGHT))
            velocity.x = p1->speed;

        p1->velocity = velocity;
    }
}

void PlayingState::Enter()
{
    // Init player1
    auto p1 = std::make_unique<Player>();
    m_players.push_back(p1.get());       // observe raw pointer before moving
    m_entities.push_back(std::move(p1)); // transfer ownership

    // TESTING LEVEL 0 -----------------------------------------------------
    auto ball1 = std::make_unique<Ball>();
    m_balls.push_back(ball1.get());
    m_entities.push_back(std::move(ball1));

    // add a second ball for testing
    auto ball2 = std::make_unique<Ball>(200.0f, 200.0f, 30.0f, 60.0f, GREEN);
    m_balls.push_back(ball2.get());
    m_entities.push_back(std::move(ball2));
    // ---------------------------------------------------------------------

    // Set Active all the m_entities
    for (auto &entity : m_entities)
    {
        entity->SetActive(true);
    }
}

void PlayingState::Update()
{
    // Physics Update
    for (auto &entity : m_entities)
    {
        if (entity->GetShapeType() == ShapeType::CIRCLE)
        {
            Physics::UpdateBall(*entity);
        }
        else if (entity->GetShapeType() == ShapeType::RECTANGLE)
        {
            Physics::UpdateCharacter(*entity);
        }
    }

    // Ball-Player Collision Detection
    for (auto &ball : m_balls)
    {
        for (auto &player : m_players)
        {
            if (Physics::CheckBallPlayerCollision(*ball, *player))
            {
                RequestStateChange(GameStateRequest::ChangeToGameOver);
                return;
            }
        }
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