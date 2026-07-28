#include "PlayingState.h"
#include "Player.h"
#include "Ball.h"
#include "raylib.h"

PlayingState::PlayingState()
{
}

void PlayingState::HandleInput()
{
    // Input Handling for Player 1
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
    m_players.push_back(p1.get());
    m_entities.push_back(std::move(p1));

    // Init ball
    m_entities.push_back(std::make_unique<Ball>());

    // add a second ball for testing
    m_entities.push_back(std::make_unique<Ball>(200.0f, 200.0f, 30.0f, 150.0f, 60.0f, GREEN));

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
}

void PlayingState::Draw()
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