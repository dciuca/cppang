#include "raylib.h"
#include "IEntity.h"

enum class ShapeType
{
    CIRCLE,
    RECTANGLE
};

class Physics
{
public:
    static void UpdateCharacter(IEntity &entity);
    static void UpdateBall(IEntity &entity);

private:
    static void ApplyGravity(IEntity &entity, float gravity = 9.8f);
    static void BounceOnWalls(IEntity &entity, float width, float height, ShapeType shape);
};