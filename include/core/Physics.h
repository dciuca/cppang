#pragma once

#include "raylib.h"
#include "IEntity.h"
#include "GameTypes.h"

class Physics
{
public:
    static void UpdateCharacter(IEntity &entity);
    static void UpdateBall(IEntity &entity);
    static bool CheckCircleRectCollision(const IEntity &ball, const IEntity &player);
    static bool CheckAndResolveCircleRectCollision(IEntity& circle, const IEntity& rect);

private:
    static void ApplyGravity(IEntity &entity, float gravity = 9.8f);
    static void BounceOnWalls(IEntity &entity, float width, float height);
    static void UpdatePosition(IEntity &entity);
};