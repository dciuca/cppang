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
    Texture2D texture;
};

struct ObstacleConfig
{
    float x;
    float y;
    float width;
    float height;
    Color color;
    Texture2D texture;
};

struct GameLevels
{
    static const int MAX_LEVELS = 3;

    // ---- Balls Configuration ----
    static std::vector<BallsConfig> GetLevelBalls(int level)
    {
        switch (level)
        {
        // ---- TEST LEVEL 0 ----
        case 0:
            return {
                {400.0f, 300.0f, 20.0f, 45.0f, RED}, // ball 1
            };

        // ---- LEVEL 1 ----
        case 1:
            return {
                {400.0f, 300.0f, 60.0f, 45.0f, GREEN}, // ball 1
                {500.0f, 250.0f, 40.0f, 30.0f, BLUE}   // ball 2
            };

        // ---- LEVEL 2 ----
        case 2:
            return {
                {300.0f, 200.0f, 50.0f, 30.0f, PURPLE}, // ball 1
                {500.0f, 400.0f, 30.0f, 60.0f, YELLOW}, // ball 2
                {700.0f, 200.0f, 40.0f, 45.0f, BLACK}   // ball 3
            };

        // ---- LEVEL 3 ----
        case 3:
            return {
                {300.0f, 200.0f, 50.0f, 30.0f, PURPLE}, // ball 1
                {500.0f, 400.0f, 30.0f, 60.0f, YELLOW}, // ball 2
                {700.0f, 200.0f, 40.0f, 45.0f, BLACK},  // ball 3
                {700.0f, 200.0f, 40.0f, 45.0f, ORANGE}  // ball 4
            };

        default:
            return {
                {400.0f, 300.0f, 60.0f, 45.0f, RED}, // ball 1
            };
        }
    }

    // ---- Obstacles Configuration ----
    static std::vector<ObstacleConfig> GetLevelObstacles(int level)
    {
        switch (level)
        {
        // ---- TEST LEVEL 0 ----
        case 0:
            return {
                {400.0f, 400.0f, 150.0f, 15.0f, GRAY}, // obstacle 1
            };
        
        // ---- LEVEL 1 ----
        case 1:
            return {
                {300.0f, 400.0f, 150.0f, 15.0f, GRAY}, // obstacle 1
                {500.0f, 200.0f, 100.0f, 15.0f, GRAY}  // obstacle 2
            };

        // ---- LEVEL 2 ----
        case 2:
            return {
                {200.0f, 300.0f, 150.0f, 15.0f, GRAY}, // obstacle 1
                {400.0f, 500.0f, 100.0f, 15.0f, GRAY}, // obstacle 2
                {600.0f, 300.0f, 150.0f, 15.0f, GRAY}  // obstacle 3
            };

        // ---- LEVEL 3 ----
        case 3:
            return {
                {200.0f, 300.0f, 150.0f, 15.0f, GRAY}, // obstacle 1
                {400.0f, 500.0f, 100.0f, 15.0f, GRAY}, // obstacle 2
                {600.0f, 300.0f, 150.0f, 15.0f, GRAY}, // obstacle 3
                {500.0f, 400.0f, 200.0f, 15.0f, GRAY}  // obstacle 4
            };

        default:
            return {
                
            };
        }
    }
};