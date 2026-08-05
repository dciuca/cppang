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
    float speed;
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

    //
    // BACKGROUND CONFIGURATION
    //
    static BackgroundConfig GetLevelBackground(int level)
    {
        return {"assets/backgrounds_col.png", {0, level * 200.0f, 255, 191}};
    }

    //
    // BALLS CONFIGURATION
    //
    static std::vector<BallsConfig> GetLevelBalls(int level)
    {
        switch (level)
        {
        // ---- TEST LEVEL 0 ----
        case 0:
            return {
                {400.0f, 200.0f, 40.0f, 45.0f, 80.0f, WHITE, "assets/balls/red.png"},
            };

        // ---- LEVEL 1 ----
        case 1:
            return {
                {260.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {280.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {300.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {320.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {340.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {360.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {380.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {400.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},

                {420.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {440.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {460.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {480.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {500.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {520.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {540.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {560.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"}
            };

        // ---- LEVEL 2 ----
        case 2:
            return {
                {300.0f, 50.0f, 50.0f, 30.0f, 100.0f, WHITE, "assets/balls/blue.png"},
                {500.0f, 70.0f, 30.0f, 60.0f, 200.0f, WHITE, "assets/balls/blue.png"},
                {700.0f, 90.0f, 40.0f, 45.0f, 250.0f, WHITE, "assets/balls/red.png"},
            };

        // ---- LEVEL 3 ----
        case 3:
            return {
                {300.0f, 100.0f, 50.0f, 30.0f, 200.0f, WHITE, "assets/balls/green.png"},
                {500.0f, 50.0f, 30.0f, 60.0f, 250.0f, WHITE, "assets/balls/blue.png"},
                {700.0f, 100.0f, 40.0f, 45.0f, 300.0f, WHITE, "assets/balls/red.png"},
            };

        default:
            return {
                {400.0f, 300.0f, 60.0f, 45.0f, 250.0f, RED},
            };
        }
    }

    //
    // OBSTACLES CONFIGURATION
    //
    static std::vector<ObstacleConfig> GetLevelObstacles(int level)
    {
        switch (level)
        {
        // ---- TEST LEVEL 0 ----
        case 0:
            return {
                {200.0f-64.0f, 200.0f, 128.0f, 15.0f, true, WHITE, "assets/obstacle.png"},
                {600.0f-64.0f, 200.0f, 128.0f, 15.0f, true, WHITE, "assets/obstacle.png"},
            };

        // ---- LEVEL 1 ----
        case 1:
            return {
                {200.0f-32.0f, 150.0f, 64.0f, 15.0f, true, WHITE, "assets/obstacle.png"},
                {600.0f-32.0f, 150.0f, 64.0f, 15.0f, true, WHITE, "assets/obstacle.png"},
            };

        // ---- LEVEL 2 ----
        case 2:
            return {
                {500.0f, 200.0f, 128.0f, 15.0f, false, WHITE, "assets/obstacle.png"}};

        // ---- LEVEL 3 ----
        case 3:
            return {
                {200.0f, 300.0f, 128.0f, 15.0f, false, WHITE, "assets/obstacle.png"},
                {400.0f, 500.0f, 64.0f, 15.0f, true, WHITE, "assets/obstacle.png"}};

        default:
            return {

            };
        }
    }
};