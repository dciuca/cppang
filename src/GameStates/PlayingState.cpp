#include "PlayingState.h"
#include "raylib.h"

PlayingState::PlayingState()
{
}

void PlayingState::Enter()
{
    // Initialize player at the center and the bottom of the screen
    player = std::make_unique<Player>();
    // player->SetTexture("assets/player.png");

    player->SetActive(true);
}

void PlayingState::Update()
{
    if (player && player->isActive)
    {
        player->Update();
        player->ClampToScreen(800); // Assuming screen width is 800
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