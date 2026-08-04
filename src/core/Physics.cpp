#include "Physics.h"
#include <cmath>

// public methods
void Physics::UpdateCharacter(IEntity &entity)
{
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

void Physics::UpdateObstacle(IEntity &entity)
{
    UpdatePosition(entity);

    const Vector2 dims = entity.GetDimensions();
    BounceOnWalls(entity, dims.x, dims.y);
};

bool Physics::CheckCircleRectCollision(const IEntity &ball, const IEntity &entity)
{
    const Vector2 ballDims = ball.GetDimensions();
    const Vector2 entityDims = entity.GetDimensions();
    float radius = ballDims.x;

    // Find the closest point on the rectangle to the circle center
    float closestX = fmaxf(entity.position.x, fminf(ball.position.x, entity.position.x + entityDims.x));
    float closestY = fmaxf(entity.position.y, fminf(ball.position.y, entity.position.y + entityDims.y));

    // Check if the distance from circle center to closest point is less than radius
    float dx = ball.position.x - closestX;
    float dy = ball.position.y - closestY;
    bool collision = (dx * dx + dy * dy) < (radius * radius);
    return collision;
}

bool Physics::CheckRectRectCollision(const IEntity &rect1, const IEntity &rect2)
{
    const Vector2 rect1Dims = rect1.GetDimensions();
    const Vector2 rect2Dims = rect2.GetDimensions();

    bool collisionX = rect1.position.x + rect1Dims.x >= rect2.position.x &&
                      rect2.position.x + rect2Dims.x >= rect1.position.x;
    bool collisionY = rect1.position.y + rect1Dims.y >= rect2.position.y &&
                      rect2.position.y + rect2Dims.y >= rect1.position.y;

    return collisionX && collisionY;
}

bool Physics::CheckAndResolveCircleRectCollision(IEntity &circle, const IEntity &rect)
{
    const Vector2 circleDims = circle.GetDimensions();
    const Vector2 rectDims = rect.GetDimensions();
    float radius = circleDims.x;

    // Find the closest point on the rectangle to the circle center
    float closestX = fmaxf(rect.position.x, fminf(circle.position.x, rect.position.x + rectDims.x));
    float closestY = fmaxf(rect.position.y, fminf(circle.position.y, rect.position.y + rectDims.y));

    // Check if the distance from circle center to closest point is less than radius
    float dx = circle.position.x - closestX;
    float dy = circle.position.y - closestY;
    float distSq = dx * dx + dy * dy;

    // No Collision, return early
    if (distSq >= radius * radius)
        return false;

    float distance = sqrtf(distSq);

    // Ball is exactly at the corner of the rectangle, resolve by pushing it out in the direction of least penetration
    if (distance < 0.0001f)
    {
        float left = circle.position.x - rect.position.x;
        float right = (rect.position.x + rectDims.x) - circle.position.x;
        float top = circle.position.y - rect.position.y;
        float bottom = (rect.position.y + rectDims.y) - circle.position.y;

        float minDist = fminf(fminf(left, right), fminf(top, bottom));

        if (minDist == left)
        {
            circle.position.x = rect.position.x - radius - 0.1f;
            circle.velocity.x = -fabs(circle.velocity.x);
        }
        else if (minDist == right)
        {
            circle.position.x = rect.position.x + rectDims.x + radius + 0.1f;
            circle.velocity.x = fabs(circle.velocity.x);
        }
        else if (minDist == top)
        {
            circle.position.y = rect.position.y - radius - 0.1f;
            circle.velocity.y = -fabs(circle.velocity.y);
        }
        else
        {
            circle.position.y = rect.position.y + rectDims.y + radius + 0.1f;
            circle.velocity.y = fabs(circle.velocity.y);
        }
        return true;
    }
    // Resolve collision by moving the circle out of the rectangle along the normal
    float overlap = radius - distance;
    Vector2 normal = {dx / distance, dy / distance};

    circle.position.x += normal.x * (overlap + 0.5f);
    circle.position.y += normal.y * (overlap + 0.5f);

    if (fabs(normal.x) > fabs(normal.y))
    {
        circle.velocity.x = -circle.velocity.x;
    }
    else
    {
        circle.velocity.y = -circle.velocity.y;
    }

    return true;
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
    int screenHeight = GetScreenHeight() - IEntity::GROUND_OFFSET;
    ;

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
