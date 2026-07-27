#include "Physics.h"

void Physics::BounceOnXY(IEntity &entity, float width)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Left and right walls
    if (entity.position.x - width <= 0)
    {
        entity.position.x = width;
        entity.velocity.x = -entity.velocity.x;
    }
    else if (entity.position.x + width >= screenWidth)
    {
        entity.position.x = screenWidth - width;
        entity.velocity.x = -entity.velocity.x;
    }

    // Top wall
    if (entity.position.y - width <= 0)
    {
        entity.position.y = width;
        entity.velocity.y = -entity.velocity.y;
    }
    // Bottom wall
    if (entity.position.y + width >= screenHeight)
    {
        entity.position.y = screenHeight - width;
        entity.velocity.y = -entity.velocity.y;
    }
};

void Physics::BounceOnX(IEntity &entity, float width)
{
    int screenWidth = GetScreenWidth();

    // Left and right walls
    if (entity.position.x < 0)
    {
        entity.position.x = 0;
        entity.velocity.x = -entity.velocity.x;
    }
    else if (entity.position.x + width > screenWidth)
    {
        entity.position.x = screenWidth - width;
        entity.velocity.x = -entity.velocity.x;
    }
};