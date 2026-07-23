#include "GameLoop.h"
#include "raylib.h"

int main() {
    
    InitWindow(800, 600, "PANG!");
    SetTargetFPS(60);
    
    GameLoop gameLoop;
    gameLoop.Run();

    CloseWindow();
}