#include "GameLoop.h"
#include "raylib.h"

int main()
{
    InitWindow(800, 600, "CPPANG!");
    SetTargetFPS(60);

    GameLoop gameLoop;
    gameLoop.Run();

    CloseWindow();
}