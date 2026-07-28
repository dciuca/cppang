#include "Physics.h"
#include <cmath>
#include <iostream> // DEBUG

// public methods
void Physics::UpdateCharacter(IEntity &entity)
{
    ApplyGravity(entity);
    UpdatePosition(entity);
    entity.velocity = {0, 0}; // Stops character releasing the key

    const Vector2 dims = entity.GetDimensions();
    BounceOnWalls(entity, dims.x, dims.y);
};

void Physics::UpdateBall(IEntity &entity)
{
    ApplyGravity(entity);
    UpdatePosition(entity);

    const Vector2 dims = entity.GetDimensions();
    BounceOnWalls(entity, dims.x, dims.y);
};

bool Physics::CheckBallPlayerCollision(const IEntity &ball, const IEntity &player)
{
    const Vector2 ballDims = ball.GetDimensions();
    const Vector2 playerDims = player.GetDimensions();
    float radius = ballDims.x;

    // Find the closest point on the rectangle to the circle center
    float closestX = fmaxf(player.position.x, fminf(ball.position.x, player.position.x + playerDims.x));
    float closestY = fmaxf(player.position.y, fminf(ball.position.y, player.position.y + playerDims.y));

    // Check if the distance from circle center to closest point is less than radius
    float dx = ball.position.x - closestX;
    float dy = ball.position.y - closestY;

    bool collision = (dx * dx + dy * dy) < (radius * radius);
    if (collision)
        std::cout << "Collision: " << collision << std::endl;
    return collision;
}

// private methods
void Physics::ApplyGravity(IEntity &entity, float gravity)
{
    entity.velocity.y += gravity;
};

void Physics::UpdatePosition(IEntity &entity)
{
    entity.position.x += entity.velocity.x * GetFrameTime();
    entity.position.y += entity.velocity.y * GetFrameTime();
}

void Physics::BounceOnWalls(IEntity &entity, float width, float height)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Calc margins depending on the shape
    const ShapeType shape = entity.GetShapeType();
    float leftOffset = (shape == ShapeType::CIRCLE) ? width : 0;
    float rightOffset = width;
    float topOffset = (shape == ShapeType::CIRCLE) ? height : 0;
    float bottomOffset = height;

    // Bounce Left/Right Walls
    if (entity.position.x - leftOffset <= 0)
    {
        entity.position.x = leftOffset;
        entity.velocity.x = -entity.velocity.x;
    }
    else if (entity.position.x + rightOffset >= screenWidth)
    {
        entity.position.x = screenWidth - rightOffset;
        entity.velocity.x = -entity.velocity.x;
    }

    // Bounce Top/Bottom Walls
    if (entity.position.y - topOffset <= 0)
    {
        entity.position.y = topOffset;
        entity.velocity.y = -entity.velocity.y;
    }
    else if (entity.position.y + bottomOffset >= screenHeight)
    {
        entity.position.y = screenHeight - bottomOffset;
        entity.velocity.y = -entity.velocity.y;
    }
};