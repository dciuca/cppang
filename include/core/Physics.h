#pragma once

#include "IEntity.h"

class Physics
{
public:
    static void UpdateCharacter(IEntity &entity);
    static void UpdateBall(IEntity &entity);
    static void UpdateObstacle(IEntity &entity);
    static void UpdateCollectible(IEntity &entity);
    static bool CheckCircleRectCollision(const IEntity &ball, const IEntity &player);
    static bool CheckAndResolveCircleRectCollision(IEntity& circle, const IEntity& rect);
    static bool CheckRectRectCollision(const IEntity &rect1, const IEntity &rect2);

private:
    static void ApplyGravity(IEntity &entity, float gravity = 9.8f);
    static void BounceOnWalls(IEntity &entity, float width, float height);
    static void TouchTheGround(IEntity &entity, float height);
    static void UpdatePosition(IEntity &entity);
};