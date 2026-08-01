#include "raylib.h"
#include <vector>

#pragma once

struct BallsConfig
{
    float x;
    float y;
    float radius;
    float angle;
    Color color;
};

struct GameLevels
{
    static std::vector<BallsConfig> GetLevelBalls(int level)
    {
        switch (level)
        {
        // ---- LEVEL 0 ----
        case 0:
            return {
                {400.0f, 300.0f, 60.0f, 45.0f, RED}, // ball 1
                {500.0f, 250.0f, 40.0f, 30.0f, BLUE} // ball 2
            };

        // ---- LEVEL 1 ----
        case 1:
            return {
                {300.0f, 200.0f, 50.0f, 30.0f, RED},  // ball 1
                {500.0f, 400.0f, 30.0f, 60.0f, BLUE}, // ball 2
                {700.0f, 200.0f, 40.0f, 45.0f, GREEN} // ball 3
            };
        }
    }
};