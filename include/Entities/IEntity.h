#pragma once

#include <string>
#include "raylib.h"
#include "GameTypes.h"

class IEntity
{
public:
    Vector2 position = {0, 0};
    Vector2 velocity = {0, 0};
    float speed = 0.0f;

public:
    virtual ~IEntity() = default;

    // default implementations
    void SetActive(bool active) { this->isActive = active; };
    bool IsActive() { return isActive; };

    // pure virtual
    virtual Vector2 GetDimensions() = 0;
    virtual void SetColor(Color newColor) = 0;
    virtual void SetTexture(const std::string &texturePath) = 0;
    virtual ShapeType GetShapeType() = 0;
    // virtual void Update() = 0;
    virtual void Draw() = 0;

private:
    bool isActive;
};