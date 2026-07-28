#include "Physics.h"
#include <cmath>

void Physics::ApplyGravity(IEntity &entity, float gravity)
{
    entity.velocity.y += gravity;
};

void Physics::UpdateCharacter(IEntity &entity)
{
    ApplyGravity(entity);

    entity.position.x += entity.velocity.x * GetFrameTime();
    entity.position.y += entity.velocity.y * GetFrameTime();
    entity.velocity = {0, 0};

    BounceOnWalls(entity, (entity.GetDimensions()).x, (entity.GetDimensions()).y, ShapeType::RECTANGLE);
};

void Physics::UpdateBall(IEntity &entity)
{
    ApplyGravity(entity);
    entity.position.x += entity.velocity.x * GetFrameTime();
    entity.position.y += entity.velocity.y * GetFrameTime();
    BounceOnWalls(entity, (entity.GetDimensions()).x, (entity.GetDimensions()).y, ShapeType::CIRCLE);
};

void Physics::BounceOnWalls(IEntity &entity, float width, float height, ShapeType shape)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Calc margins depending on the shape
    float leftOffset = (shape == ShapeType::CIRCLE) ? width : 0;
    float rightOffset = (shape == ShapeType::CIRCLE) ? width : width;
    float topOffset = (shape == ShapeType::CIRCLE) ? height : 0;
    float bottomOffset = (shape == ShapeType::CIRCLE) ? height : height;

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