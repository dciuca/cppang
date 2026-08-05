#include "raylib.h"
#include <vector>
#include <string>

#pragma once

struct BallsConfig
{
    float x;
    float y;
    float radius;
    float angle;
    float speed = 250.0f;
    Color color;
    std::string texturePath;
};

struct ObstacleConfig
{
    float x;
    float y;
    float width;
    float height;
    bool isFixed;
    Color color;
    std::string texturePath;
};

struct BackgroundConfig
{
    std::string texturePath;
    Rectangle sourceRect;
};

struct GameLevels
{
    static const int MAX_LEVELS = 3;

    // ---- Background Configuration ----
    static BackgroundConfig GetLevelBackground(int level)
    {
        return {"assets/backgrounds_col.png", {0, level * 200.0f, 255, 191}};
    }

    // ---- Balls Configuration ----
    static std::vector<BallsConfig> GetLevelBalls(int level)
    {
        switch (level)
        {
        // ---- TEST LEVEL 0 ----
        case 0:
            return {
                {400.0f, 300.0f, 40.0f, 45.0f, 200.0f, WHITE, "assets/balls/red.png"},
            };

        // ---- LEVEL 1 ----
        case 1:
            return {
                {400.0f, 300.0f, 60.0f, 45.0f, 250.0f, GREEN},
                {500.0f, 250.0f, 40.0f, 30.0f, 250.0f, BLUE},
            };

        // ---- LEVEL 2 ----
        case 2:
            return {
                {300.0f, 200.0f, 50.0f, 30.0f, 300.0f, PURPLE},
                {500.0f, 400.0f, 30.0f, 60.0f, 300.0f, YELLOW},
                {700.0f, 200.0f, 40.0f, 45.0f, 300.0f, BLACK},
            };

        // ---- LEVEL 3 ----
        case 3:
            return {
                {300.0f, 200.0f, 50.0f, 30.0f, 350.0f, PURPLE},
                {500.0f, 400.0f, 30.0f, 60.0f, 350.0f, YELLOW},
                {700.0f, 200.0f, 40.0f, 45.0f, 350.0f, BLACK},
                {700.0f, 200.0f, 40.0f, 45.0f, 350.0f, ORANGE},
            };

        default:
            return {
                {400.0f, 300.0f, 60.0f, 45.0f, 250.0f, RED},
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
            return {};

        // ---- LEVEL 1 ----
        case 1:
            return {
                {300.0f, 400.0f, 150.0f, 15.0f, true, GRAY}, // obstacle 1
                {500.0f, 200.0f, 100.0f, 15.0f, false, GRAY} // obstacle 2
            };

        // ---- LEVEL 2 ----
        case 2:
            return {
                {200.0f, 300.0f, 150.0f, 15.0f, false, GRAY}, // obstacle 1
                {400.0f, 500.0f, 100.0f, 15.0f, false, GRAY}, // obstacle 2
                {600.0f, 300.0f, 150.0f, 15.0f, false, GRAY}  // obstacle 3
            };

        // ---- LEVEL 3 ----
        case 3:
            return {
                {200.0f, 300.0f, 150.0f, 15.0f, true, GRAY},  // obstacle 1
                {400.0f, 500.0f, 100.0f, 15.0f, true, GRAY},  // obstacle 2
                {600.0f, 300.0f, 150.0f, 15.0f, false, GRAY}, // obstacle 3
                {500.0f, 400.0f, 200.0f, 15.0f, false, GRAY}  // obstacle 4
            };

        default:
            return {

            };
        }
    }
};