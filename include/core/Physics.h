#include "raylib.h"
#include "IEntity.h"

class Physics
{
public:
    static void BounceOnXY(IEntity &entity, float width);
    static void BounceOnX(IEntity &entity, float width);
};