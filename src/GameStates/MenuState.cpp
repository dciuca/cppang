#include "MenuState.h"
#include "raylib.h"

MenuState::MenuState()
{
}

void MenuState::HandleInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        RequestStateChange(GameStateRequest::ChangeToPlaying);
    }
    else if (IsKeyPressed(KEY_ESCAPE))
    {
        RequestStateChange(GameStateRequest::Quit);
    }
}

void MenuState::Enter()
{
    gameStateRequest = GameStateRequest::None;
}

void MenuState::Update()
{
    // Any updates for menu state, if needed   
}

void MenuState::Draw()
{
    BeginDrawing();
    ClearBackground(GREEN);

    // Draw MENU text centered
    const char* text = "MENU";
    int fontSize = 60;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    
    int textWidth = MeasureText(text, fontSize);
    int textX = (screenWidth - textWidth) / 2;
    int textY = screenHeight / 2 - 50;
    
    DrawText(text, textX, textY, fontSize, WHITE);
    
    // Draw instructions
    const char* instructions = "Press SPACE to start the game";
    int instrSize = 30;
    int instrWidth = MeasureText(instructions, instrSize);
    int instrX = (screenWidth - instrWidth) / 2;
    int instrY = textY + 80;
    
    DrawText(instructions, instrX, instrY, instrSize, GRAY);

    DrawFPS(10, 10);
    
    EndDrawing();
}

void MenuState::Exit()
{
    // Cleanup if needed
}
