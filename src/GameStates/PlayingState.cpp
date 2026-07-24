#include "PlayingState.h"
#include "raylib.h"

PlayingState::PlayingState()
{
}

void PlayingState::Enter()
{
    // Init player
    player = std::make_unique<Player>();
    player->SetActive(true);
}

void PlayingState::Update()
{
    if (player && player->isActive)
    {
        player->Update();
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

    DrawFPS(10, 10);

    EndDrawing();
}

void PlayingState::Exit()
{
    player.reset();
}