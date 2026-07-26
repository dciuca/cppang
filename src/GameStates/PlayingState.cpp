#include "PlayingState.h"
#include "Player.h"
#include "Ball.h"
#include "raylib.h"

PlayingState::PlayingState()
{
}

void PlayingState::HandleInput() {
    // Player input handling
    if (player && player->isActive) {
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            player->velocity.x = -player->speed;
        }
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            player->velocity.x = player->speed;
        }
    }
}

void PlayingState::Enter()
{
    // Init player
    player = std::make_unique<Player>();
    player->SetActive(true);

    // Init ball
    AddBall(std::make_unique<Ball>());
    balls.back()->SetActive(true);

    // add a second ball for testing
    AddBall(std::make_unique<Ball>(200.0f, 200.0f, 30.0f, 150.0f, 60.0f, GREEN));
    balls.back()->SetActive(true);
}

void PlayingState::Update()
{
    if (player && player->isActive)
    {
        player->Update();
    }

    // Update all active balls
    for (auto& ball : balls)
    {
        if (ball && ball->isActive)
        {
            ball->Update();
        }
    }
}

void PlayingState::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (player)
    {
        player->Draw();
    }

    // Draw all active balls
    for (const auto& ball : balls)
    {
        if (ball)
        {
            ball->Draw();
        }
    }

    DrawFPS(10, 10);

    EndDrawing();
}

void PlayingState::Exit()
{
    player.reset();
    balls.clear();
}

void PlayingState::AddBall(std::unique_ptr<IEntity> newBall)
{
    balls.push_back(std::move(newBall));
}