#include "GameTypes.h"
#include "raylib.h"
#include <vector>
#include <string>

#pragma once

struct PlayerConfig
{
    float x;
    float y;
    float width;
    float height;
    Color color;
    std::string texturePath;
};

struct BallsConfig
{
    float x;
    float y;
    float radius;
    float angle;
    float speed;
    Color color;
    std::string texturePath;
    CollectibleType collectibleType = CollectibleType::None;
    int dropGeneration = 0;
};

struct ObstacleConfig
{
    float x;
    float y;
    float width;
    float height;
    bool isFixed;
    float speed;
    Color color;
    std::string texturePath;
};

struct HarpoonConfig
{
    float x;
    float y;
    float width;
    float height;
    float speed;
    Color color;
    std::string texturePath;
};

struct BackgroundConfig
{
    std::string texturePath;
    Rectangle sourceRect;
};

struct LifebarConfig
{
    std::string texturePath;
    Rectangle sourceRect;
};

struct CollectibleVisualConfig 
{
    float radius; 
    Color color; 
    std::string texturePath; 
};

struct GameLevels
{
    //
    // BACKGROUND CONFIGURATION
    //
    static BackgroundConfig GetLevelBackground(int level)
    {
        return {"assets/backgrounds_col.png", {0, (level - 1) * 200.0f, 255, 191}};
    }

    //
    // LIFEBAR CONFIGURATION
    //
    static LifebarConfig GetLifebarConfig()
    {
        return {"assets/hearth.png", {0, 0, 16, 16}};
    }

    //
    // PLAYER CONFIGURATION
    //
    static PlayerConfig GetPlayerConfig()
    {
        const float PLAYER_WIDTH = 64.0f;
        const float PLAYER_HEIGHT = 64.0f;
        return {(float)(GetScreenWidth() / 2), (float)(GetScreenHeight()) - PLAYER_HEIGHT - BORDER_OFFSET, PLAYER_WIDTH, PLAYER_HEIGHT, WHITE, "assets/player.png"};
    }

    //
    // HARPOON CONFIGURATION
    //
    static HarpoonConfig GetHarpoonConfig()
    {
        const float HARPOON_SPEED = 900.0f;
        return {0.0f, 0.0f, 30.0f, 0.0f, HARPOON_SPEED, WHITE, "assets/harpoon.png"};
    }

    //
    // BALLS CONFIGURATION
    //
    static std::vector<BallsConfig> GetLevelBalls(int level)
    {
        switch (level)
        {
        // ---- LEVEL 1 ----
        case 1:
            return {
                {400.0f, 200.0f, 40.0f, 45.0f, 80.0f, WHITE, "assets/balls/red.png", CollectibleType::Clock, 1},
            };

        // ---- LEVEL 2 ----
        case 2:
            return {
                {260.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {280.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {300.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {320.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png", CollectibleType::LifeUp, 1},
                {340.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {360.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {380.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {400.0f, 340.0f, 10.0f, 145.0f, 80.0f, WHITE, "assets/balls/blue.png"},

                {420.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {440.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {460.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {480.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png", CollectibleType::Clock, 1},
                {500.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {520.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {540.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
                {560.0f, 340.0f, 10.0f, 35.0f, 80.0f, WHITE, "assets/balls/blue.png"},
            };

        // ---- LEVEL 3 ----
        case 3:
            return {
                {300.0f, 250.0f, 50.0f, 145.0f, 120.0f, WHITE, "assets/balls/green.png", CollectibleType::LifeUp, 1},
                {500.0f, 250.0f, 50.0f, 35.0f, 120.0f, WHITE, "assets/balls/green.png", CollectibleType::Clock, 2},
            };

        // ---- LEVEL 4 ----
        case 4:
            return {
                {70.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
                {100.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
                {130.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
                {160.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
                {190.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
                {220.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png", CollectibleType::Clock, 1},
                {250.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
                {280.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},

                {530.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
                {560.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
                {590.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
                {620.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
                {650.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
                {680.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
                {710.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
                {740.0f, 40.0f, 10.0f, 0.0f, 70.0f, WHITE, "assets/balls/blue.png"},
            };

        // ---- LEVEL 5 ----
        case 5:
            return {
                // Two large fast red balls from opposite corners
                {150.0f, 100.0f, 40.0f, 45.0f, 100.0f, WHITE, "assets/balls/red.png", CollectibleType::Clock, 2},
                {650.0f, 100.0f, 40.0f, 135.0f, 100.0f, WHITE, "assets/balls/red.png"},
                // One medium green bouncing low
                {300.0f, 400.0f, 20.0f, 20.0f, 100.0f, WHITE, "assets/balls/green.png", CollectibleType::LifeUp, 1},
            };

        // ---- LEVEL 6 ----
        case 6:
            return {
                {200.0f, 80.0f, 30.0f, 45.0f, 130.0f, WHITE, "assets/balls/red.png", CollectibleType::Clock, 1},
                {600.0f, 80.0f, 30.0f, 135.0f, 130.0f, WHITE, "assets/balls/red.png"},
                {350.0f, 200.0f, 20.0f, 60.0f, 110.0f, WHITE, "assets/balls/green.png"},
                {450.0f, 200.0f, 20.0f, 120.0f, 110.0f, WHITE, "assets/balls/green.png"},
            };

        // ---- LEVEL 7 ----
        case 7:
            return {
                {400.0f, 60.0f, 40.0f, 90.0f, 90.0f, WHITE, "assets/balls/red.png", CollectibleType::Clock, 2},
                {150.0f, 120.0f, 15.0f, 30.0f, 170.0f, WHITE, "assets/balls/blue.png", CollectibleType::LifeUp, 1},
                {650.0f, 120.0f, 15.0f, 150.0f, 170.0f, WHITE, "assets/balls/blue.png"},
                {400.0f, 300.0f, 15.0f, 210.0f, 170.0f, WHITE, "assets/balls/blue.png"},
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
        // ---- TEST LEVEL 1 ----
        case 1:
            return {
                {200.0f - 64.0f, 200.0f, 128.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {600.0f - 64.0f, 200.0f, 128.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
            };

        // ---- LEVEL 2 ----
        case 2:
            return {
                {200.0f - 32.0f, 150.0f, 64.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {600.0f - 32.0f, 150.0f, 64.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
            };

        // ---- LEVEL 3 ----
        case 3:
            return {
                {200.0f - 8.0f, 250.0f, 16.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {600.0f - 8.0f, 250.0f, 16.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
            };

        // ---- LEVEL 4 ----
        case 4:
            return {
                {80.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {110.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {140.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {170.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {200.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {230.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {260.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {290.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},

                {510.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {540.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {570.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {600.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {630.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {660.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {690.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {720.0f, 22.0f, 10.0f, 400.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
            };

        // ---- LEVEL 5 ----
        // Cross shape in the center + one moving horizontal platform
        case 5:
            return {
                // Horizontal bar of the cross (center y=285, spanning x=260..540)
                {260.0f, 285.0f, 60.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {320.0f, 285.0f, 60.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {380.0f, 285.0f, 60.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {440.0f, 285.0f, 60.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {500.0f, 285.0f, 60.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},

                // One moving platform sliding horizontally at the bottom area
                {100.0f, 450.0f, 120.0f, 15.0f, false, 50.0f, WHITE, "assets/obstacle.png"},
            };

        // ---- LEVEL 6 ----
        case 6:
            return {
                {150.0f, 300.0f, 160.0f, 15.0f, false, 80.0f, WHITE, "assets/obstacle.png"},
                {550.0f, 200.0f, 160.0f, 15.0f, false, 80.0f, WHITE, "assets/obstacle.png"},
            };

        // ---- LEVEL 7 ----
        // Staggered fixed shelves — zigzag layout forcing balls to bounce between them
        case 7:
            return {
                {100.0f, 180.0f, 150.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {550.0f, 280.0f, 150.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {250.0f, 380.0f, 150.0f, 15.0f, true, 0.0f, WHITE, "assets/obstacle.png"},
                {300.0f, 150.0f, 120.0f, 15.0f, false, 60.0f, WHITE, "assets/obstacle.png"},
            };

        default:
            return {

            };
        }
    }

    //
    // COLLECTIBLES CONFIGURATION
    //    
    static CollectibleVisualConfig GetCollectibleVisualConfig(CollectibleType type)
    {
    switch (type)
    {
    case CollectibleType::Clock:  return {15.0f, WHITE, "assets/clock.png"};
    case CollectibleType::LifeUp: return {15.0f, WHITE, "assets/lifeUp.png"};
    default:                      return {15.0f, WHITE, ""};
    }
}
};