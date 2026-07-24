#include "PlayingState.h"
#include "Player.h"
#include "Ball.h"
#include "raylib.h"

PlayingState::PlayingState()
{
}

void PlayingState::Enter()
{
    // Init player
    player = std::make_unique<Player>();
    player->SetActive(true);

    // Init ball
    ball = std::make_unique<Ball>();
    ball->SetActive(true);
}

void PlayingState::Update()
{
    if (player && player->isActive)
    {
        player->Update();
    }
    if (ball && ball->isActive)
    {
        ball->Update();
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

    if (ball)
    {
        ball->Draw();
    }

    DrawFPS(10, 10);

    EndDrawing();
}

void PlayingState::Exit()
{
    player.reset();
    ball.reset();
}