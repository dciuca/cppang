#include "Physics.h"
#include <cmath>

void Physics::ApplyGravity(IEntity &entity, float gravity)
{
    entity.velocity.y += gravity;
};

void Physics::UpdatePosition(IEntity &entity)
{
    entity.position.x += entity.velocity.x * GetFrameTime();
    entity.position.y += entity.velocity.y * GetFrameTime();
}

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